#ifndef MQTT_TASK_TEMPERATURELOGIC_H
#define MQTT_TASK_TEMPERATURELOGIC_H

#include "MosquittoClientWrapper.h"
#include <string>
#include <memory>

class TemperatureLogic {
public:
    static void setData(double targetTemperature, std::shared_ptr<MosquittoClientWrapper> mosquitto);
    static void handleMosquittoMessageInfo(mosquitto_message const* msg);

private:
    static std::shared_ptr<MosquittoClientWrapper> _pMosquitto;
    static double _targetTemperature;
    static constexpr double _temperatureDifference = 0.5;
    static constexpr double _eps = 0.1;
};


#endif //MQTT_TASK_TEMPERATURELOGIC_H
