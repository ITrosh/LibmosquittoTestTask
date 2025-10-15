#ifndef MQTT_TASK_APPLICATIONSTATE_H
#define MQTT_TASK_APPLICATIONSTATE_H

#include <iostream>
#include <csignal>

enum class ApplicationState {
    Success = 0,
    IncorrectNumberOfArguments = 1,
    IncorrectSecondArgument = 2,
    IncorrectTemperature = 3,
    ConfigFileIsNotOpen = 4,
    IncorrectConfigParameter = 5,
    TemperatureIsNotRealValue = 6,
    IncorrectTemperatureLength = 7,
    InitLibmosquittoFailed = 9,
    ParsingAlarmTemperatureFailed = 10,
    InvalidConnectToMQTTBroker = 11,
    AlarmTemperatureIsNotNumber = 12,
    UnhandledException = -1
};

void printApplicationState(ApplicationState applicationState);

#endif //MQTT_TASK_APPLICATIONSTATE_H
