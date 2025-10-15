#ifndef MQTT_TASK_ALARMTEMPERATUREVALIDATOR_H
#define MQTT_TASK_ALARMTEMPERATUREVALIDATOR_H

#include "MosquittoClientWrapper.h"
#include <memory>

class AlarmTemperatureValidator {
public:
    static void setData(std::shared_ptr<MosquittoClientWrapper> mosquitto);
    static void handleAlarmTemperature(mosquitto_message const* msg);

private:
    static std::shared_ptr<MosquittoClientWrapper> _pMosquitto;
    static constexpr double _eps = 0.1;
    static constexpr double _leftBorder = -10.0;
    static constexpr double _rightBorder = 50.0;
};


#endif //MQTT_TASK_ALARMTEMPERATUREVALIDATOR_H
