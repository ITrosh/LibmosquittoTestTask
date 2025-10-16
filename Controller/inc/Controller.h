#ifndef MQTT_TASK_CONTROLLER_H
#define MQTT_TASK_CONTROLLER_H

#include "MosquittoClientWrapper.h"
#include "TemperatureLogic.h"
#include "AlarmTemperatureValidator.h"
#include <string>
#include <memory>

class Controller {
public:
    explicit Controller(std::shared_ptr<MosquittoClientWrapper> mosquitto);
    ~Controller();

    void run();

private:
    std::shared_ptr<MosquittoClientWrapper> _pMosquittoClient;
    int _rc;
};


#endif //MQTT_TASK_CONTROLLER_H
