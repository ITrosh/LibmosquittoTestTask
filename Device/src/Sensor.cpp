#include "Sensor.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <utility>
#include <cstring>

using json = nlohmann::json;

void showAlarmTemperatureResult(mosquitto_message const* msg) {
    try {
        json data = json::parse((char *) msg->payload);
        if (data.contains("status") && data.at("status").is_string() &&
            data.contains("alarm_temperature") && data.at("alarm_temperature").is_number() &&
            data.contains("message") && data.at("message").is_string()) {
            std::cout << "Alarm temperature " << data.at("alarm_temperature") << " " << data.at("status") << ": " <<
                      data.at("message") << std::endl;
        } else {
            std::cout << "Incorrect json for alarm temperature parameter!" << std::endl;
        }
    }
    catch(...) {
        std::cout << "nlohmann exception" << std::endl;
    }
}

void onMessage(mosquitto* mosquitto, void* obj, mosquitto_message const* msg) {
    std::cout << "Got new message with topic "  << msg->topic << ": " << (char*) msg->payload << std::endl;
    if (strcmp(msg->topic, "home/thermostat/heater") == 0)
        Heater::setMosquittoMessageInfo(msg);
    else if (strcmp(msg->topic, "home/thermostat/out/parameters/alarm") == 0)
        showAlarmTemperatureResult(msg);
}

Sensor::Sensor(double const& alarmTemperature, std::shared_ptr<MosquittoClientWrapper> mosquitto)
    : _pMosquitto(std::move(mosquitto))
{
    mosquitto_message_callback_set(_pMosquitto->getClient(), onMessage);

    _rc = mosquitto_connect(_pMosquitto->getClient(), "localhost", 1883, 60);
    if (_rc != 0)
        throw std::runtime_error("invalid connect to broker, error code " + std::to_string(_rc));

    std::cout << "Connected to MQTT broker" << std::endl;

    _heater.setMosquitto(_pMosquitto);
    mosquitto_subscribe(_pMosquitto->getClient(), nullptr, "home/thermostat/heater", 0);
    mosquitto_subscribe(_pMosquitto->getClient(), nullptr, "home/thermostat/out/parameters/alarm", 0);
    std::cout << "Subscribed to topics" << std::endl;

    json alarmTopicData = {
        { "alarm_temperature", alarmTemperature }
    };

    mosquitto_publish(_pMosquitto->getClient(), nullptr, "home/thermostat/in/parameters/alarm",
                      static_cast<int>(alarmTopicData.dump().size()), alarmTopicData.dump().data(), 0, false);
}

Sensor::~Sensor() {
    mosquitto_disconnect(_pMosquitto->getClient());
}

void Sensor::run() {
    _heater.run();
}
