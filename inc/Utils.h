#ifndef MQTT_TASK_UTILS_H
#define MQTT_TASK_UTILS_H

#include "ApplicationState.h"
#include <string_view>

constexpr size_t NUMBER_OF_ARGUMENTS = 3;
constexpr std::string_view CMD_LINE_SECOND_ARGUMENT = "--set-alarm-temp";

constexpr std::string_view TEMPERATURE_FILE = "../../Controller/resource/target_temperature.conf";

ApplicationState parseTemperature(std::string_view const& temperature);
ApplicationState readTargetTemperature(std::string const& filename, double& targetTemperature);

bool isSymbolInRange(char symbol, char beginSymbolInRange, char endSymbolInRange);

//void signal_handler(int signum) {
//    std::cout << "Получен сигнал " << signum << std::endl;
//    if (signum == SIGINT || signum == SIGTERM)
//        exit(0);
//    else
//        exit(signum);
//}

#endif //MQTT_TASK_UTILS_H
