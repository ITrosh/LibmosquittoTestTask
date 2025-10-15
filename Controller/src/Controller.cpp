#include "Controller.h"
#include <cstring>
#include <iostream>

void onMessage(mosquitto* mosquitto, void* obj, mosquitto_message const* msg) {
    std::cout << "Got new message with topic "  << msg->topic << ": " << (char*) msg->payload << std::endl;
    if (strcmp(msg->topic, "home/thermostat/temperature") == 0)
        TemperatureLogic::handleMosquittoMessageInfo(msg);
    else if (strcmp(msg->topic, "home/thermostat/in/parameters/alarm") == 0)
        AlarmTemperatureValidator::handleAlarmTemperature(msg);
}

Controller::Controller(std::shared_ptr<MosquittoClientWrapper> mosquitto)
    : _pMosquittoClient(std::move(mosquitto))
{
    mosquitto_message_callback_set(_pMosquittoClient->getClient(), onMessage);

    _rc = mosquitto_connect(_pMosquittoClient->getClient(), "localhost", 1883, 60);
    if (_rc != 0)
        throw std::runtime_error("invalid connect to broker, error code " + std::to_string(_rc));

    std::cout << "Connected to MQTT broker" << std::endl;

    mosquitto_subscribe(_pMosquittoClient->getClient(), nullptr, "home/thermostat/temperature", 0);
    mosquitto_subscribe(_pMosquittoClient->getClient(), nullptr, "home/thermostat/in/parameters/alarm", 0);
    std::cout << "Subscribed to topics" << std::endl;
}

Controller::~Controller() {
    mosquitto_disconnect(_pMosquittoClient->getClient());
}

void Controller::run() {
    mosquitto_loop_start(_pMosquittoClient->getClient());
    getchar();
    mosquitto_loop_stop(_pMosquittoClient->getClient(), true);
}
