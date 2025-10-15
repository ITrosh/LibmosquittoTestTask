#include "TemperatureLogic.h"
#include <nlohmann/json.hpp>
#include <cmath>
#include <iostream>

using json = nlohmann::json;

std::shared_ptr<MosquittoClientWrapper> TemperatureLogic::_pMosquitto = nullptr;
double TemperatureLogic::_targetTemperature = 0.0;

void TemperatureLogic::handleMosquittoMessageInfo(mosquitto_message const* msg) {
    try {
        json data = json::parse((char*) msg->payload);

        if (data.contains("value") && data.at("value").is_number()) {
            double temperature = data.find("value").value();

            if (fabs(temperature - _targetTemperature) > _temperatureDifference - _eps) {
                std::string str;
                if (temperature < _targetTemperature)
                    str = "ON";
                else
                    str = "OFF";

                mosquitto_publish(_pMosquitto->getClient(), nullptr, "home/thermostat/heater",
                                  static_cast<int>(str.size()), str.data(), 0, false);
            }
        }
        else {
            std::cout << "Value is not a number" << std::endl;
        }
    }
    catch (...) {
        std::cout << __PRETTY_FUNCTION__ << "nlohmann exception" << std::endl;
    }
}

void TemperatureLogic::setData(double targetTemperature, std::shared_ptr<MosquittoClientWrapper> mosquitto)
{
    _targetTemperature = targetTemperature;
    _pMosquitto = std::move(mosquitto);
}
