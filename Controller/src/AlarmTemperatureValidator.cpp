#include "AlarmTemperatureValidator.h"
#include "nlohmann/json.hpp"
#include <string_view>
#include <string>
#include <iostream>

using json = nlohmann::json;

std::shared_ptr<MosquittoClientWrapper> AlarmTemperatureValidator::_pMosquitto = nullptr;

void AlarmTemperatureValidator::handleAlarmTemperature(mosquitto_message const* msg) {
    try {
        json data = json::parse((char*) msg->payload);

        std::string status = "rejected";
        std::string message;
        double alarmTemperature = 0.0;

        if (data.contains("alarm_temperature") && data.at("alarm_temperature").is_number()) {
            alarmTemperature = data.find("alarm_temperature").value();

            if (alarmTemperature > _leftBorder - _eps && alarmTemperature < _rightBorder + _eps) {
                status = "accepted";
                message = "Alarm temperature set successfully";
            }
            else {
                message = "Temperature out of valid range (";

                std::stringstream stream;
                stream << std::fixed << std::setprecision(1) << _leftBorder;
                message.append(stream.str()).append(" to ");
                stream.str("");
                stream.clear();

                stream << std::fixed << std::setprecision(1) << _rightBorder;
                message.append(stream.str()).append(")");
            }
        }
        else {
            message = "Value is not a number";
        }

        json alarmTemperatureValidation = {
                {"status",            status},
                {"alarm_temperature", alarmTemperature},
                {"message",           message}
        };

        mosquitto_publish(_pMosquitto->getClient(), nullptr, "home/thermostat/out/parameters/alarm",
                          static_cast<int>(alarmTemperatureValidation.dump().size()),
                          alarmTemperatureValidation.dump().data(), 0, false);
    }
    catch (...) {
        std::cout << __PRETTY_FUNCTION__ << " nlohmann exception" << std::endl;
    }
}

void AlarmTemperatureValidator::setData(std::shared_ptr<MosquittoClientWrapper> mosquitto)
{
    _pMosquitto = std::move(mosquitto);
}