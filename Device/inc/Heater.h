#ifndef DEVICE_HEATER_H
#define DEVICE_HEATER_H

#include "MosquittoClientWrapper.h"
#include <mosquitto.h>
#include <memory>
#include <mutex>
#include <thread>
#include <atomic>

class Heater {
public:
    Heater() = default;
    ~Heater();

    void run();
    void setMosquitto(std::shared_ptr<MosquittoClientWrapper> mosquitto);

    static void setMosquittoMessageInfo(mosquitto_message const* msg);

private:
    static std::atomic<bool> _isHeaterTurnedOn;

    std::thread _publishTemperatureThread;
    std::thread _temperatureLogicThread;
    std::shared_ptr<MosquittoClientWrapper> _pMosquitto;
    std::mutex _temperatureMutex;
    double _temperature = 20.0;
    bool _isThreadsRunning = true;

    void publishTemperature();
    void changeTemperature();
};


#endif //DEVICE_HEATER_H
