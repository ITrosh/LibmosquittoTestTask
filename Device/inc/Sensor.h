#ifndef DEVICE_SENSOR_H
#define DEVICE_SENSOR_H

#include "MosquittoClientWrapper.h"
#include "Heater.h"
#include <mosquitto.h>

void onMessage(mosquitto* mosquitto, void* obj, mosquitto_message const* msg);

class Sensor {
public:
    Sensor(double const& alarmTemperature, std::shared_ptr<MosquittoClientWrapper> mosquitto);
    ~Sensor();

    void run();

private:
    int _rc;
    std::shared_ptr<MosquittoClientWrapper> _pMosquitto;
    Heater _heater;

};

#endif //DEVICE_SENSOR_H
