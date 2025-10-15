#include "ApplicationState.h"

void printApplicationState(ApplicationState applicationState) {
    switch (applicationState) {
        case ApplicationState::UnhandledException:
            std::cout << "UnhandledException!" << std::endl;
            break;
        case ApplicationState::AlarmTemperatureIsNotNumber:
            std::cout << "Alarm temperature is not a number!" << std::endl;
            break;
        case ApplicationState::InvalidConnectToMQTTBroker:
            std::cout << "Could not connect to MQTT broker!" << std::endl;
            break;
        case ApplicationState::ParsingAlarmTemperatureFailed:
            std::cout << "Parsing of alarm temperature parameter is failed!" << std::endl;
            break;
        case ApplicationState::InitLibmosquittoFailed:
            std::cout << "Libmosquitto init is failed!" << std::endl;
            break;
        case ApplicationState::IncorrectTemperature:
            std::cout << "Temperature parameter is incorrect!" << std::endl;
            break;
        case ApplicationState::IncorrectTemperatureLength:
            std::cout << "The length of temperature parameter is incorrect!" << std::endl;
            break;
        case ApplicationState::TemperatureIsNotRealValue:
            std::cout << "Temperature is not a real value!" << std::endl;
            break;
        case ApplicationState::IncorrectConfigParameter:
            std::cout << "Incorrect parameter name in config!" << std::endl;
            break;
        case ApplicationState::ConfigFileIsNotOpen:
            std::cout << "Config file is not open!" << std::endl;
            break;
        case ApplicationState::IncorrectSecondArgument:
            std::cout << "Second command line argument is incorrect!" << std::endl;
            break;
        case ApplicationState::IncorrectNumberOfArguments:
            std::cout << "Number of command line arguments is incorrect!" << std::endl;
            break;
        default:
            std::cout << "Everything is good" << std::endl;
    }
}