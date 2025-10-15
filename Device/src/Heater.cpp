#include "Heater.h"
#include "nlohmann/json.hpp"
#include <thread>
#include <utility>
#include <cstring>

using json = nlohmann::json;

std::atomic<bool> Heater::_isHeaterTurnedOn = false;

void Heater::run() {
    _publishTemperatureThread = std::thread(&Heater::publishTemperature, this);
    _temperatureLogicThread = std::thread(&Heater::changeTemperature, this);

    mosquitto_loop_start(_pMosquitto->getClient());
    getchar();
    mosquitto_loop_stop(_pMosquitto->getClient(), true);
}

void Heater::setMosquitto(std::shared_ptr<MosquittoClientWrapper> mosquitto) {
    _pMosquitto = std::move(mosquitto);
}

void Heater::publishTemperature() {
    while (_isThreadsRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::lock_guard<std::mutex> lk(_temperatureMutex);
        json temperatureData = {
            { "value", _temperature }
        };

        mosquitto_publish(_pMosquitto->getClient(), nullptr, "home/thermostat/temperature",
                          static_cast<int>(temperatureData.dump().size()), temperatureData.dump().data(), 0, false);
    }
}

void Heater::changeTemperature() {
    while (_isThreadsRunning) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lk(_temperatureMutex);
        if (_isHeaterTurnedOn.load())
            _temperature += 0.5;
        else
            _temperature -= 0.5;
    }
}

void Heater::setMosquittoMessageInfo(mosquitto_message const* msg) {
    if (strcmp((char*)msg->payload, "ON") == 0)
        _isHeaterTurnedOn.store(true);
    else
        _isHeaterTurnedOn.store(false);
}

Heater::~Heater() {
    _isThreadsRunning = false;

    if (_publishTemperatureThread.joinable())
        _publishTemperatureThread.join();

    if (_temperatureLogicThread.joinable())
        _temperatureLogicThread.join();
}
