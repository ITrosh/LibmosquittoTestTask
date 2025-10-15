#ifndef MQTT_TASK_UTILS_H
#define MQTT_TASK_UTILS_H

#include "ApplicationState.h"

ApplicationState parseTemperature(std::string_view const& temperature);

bool isSymbolInRange(char symbol, char beginSymbolInRange, char endSymbolInRange);

//void signal_handler(int signum) {
//    std::cout << "Получен сигнал " << signum << std::endl;
//    if (signum == SIGINT || signum == SIGTERM)
//        exit(0);
//    else
//        exit(signum);
//}

#endif //MQTT_TASK_UTILS_H
