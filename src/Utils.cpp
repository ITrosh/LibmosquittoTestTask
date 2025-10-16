#include "Utils.h"
#include <fstream>

bool isSymbolInRange(char symbol, char beginSymbolInRange, char endSymbolInRange) {
    return symbol >= beginSymbolInRange && symbol <= endSymbolInRange;
}

ApplicationState parseTemperature(std::string_view const& temperature) {
    size_t pos = temperature.find('.');
    if (pos != std::string::npos) {
        std::string_view integerPart = temperature.substr(0, pos);
        std::string_view realPart = temperature.substr(pos + 1);

        if (integerPart.size() <= 3 && !integerPart.empty() && realPart.size() == 1) {
            bool isNegativeTwoDigitIntegerPart = integerPart.size() == 3 && integerPart.at(0) == '-' &&
                                                 isSymbolInRange(integerPart.at(1), '1', '9') &&
                                                 isSymbolInRange(integerPart.at(2), '0', '9');

            bool isNegativeOneDigitIntegerPart = integerPart.size() == 2 && integerPart.at(0) == '-' &&
                                                 (isSymbolInRange(integerPart.at(1), '1', '9') ||
                                                  (integerPart.at(1) == '0' && realPart.at(0) == '5'));

            bool isPositiveTwoDigitIntegerPart = integerPart.size() == 2 &&
                                                 (isSymbolInRange(integerPart.at(0), '1', '9') &&
                                                  isSymbolInRange(integerPart.at(1), '0', '9'));

            bool isPositiveOneDigitIntegerPart = integerPart.size() == 1 &&
                                                 isSymbolInRange(integerPart.at(0), '0', '9');

            bool isCorrectIntegerPart = isNegativeTwoDigitIntegerPart || isNegativeOneDigitIntegerPart ||
                                        isPositiveTwoDigitIntegerPart || isPositiveOneDigitIntegerPart;

            if (isCorrectIntegerPart && (realPart.at(0) == '0' || realPart.at(0) == '5')) {
                return ApplicationState::Success;
            }
            else {
                return ApplicationState::IncorrectTemperature;
            }
        }
        else {
            return ApplicationState::IncorrectTemperatureLength;
        }
    }
    else {
        return ApplicationState::TemperatureIsNotRealValue;
    }
}

ApplicationState readTargetTemperature(std::string const& filename, double& targetTemperature) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        std::getline(file, line);
        file.close();

        size_t pos = line.find('=');
        if (pos != std::string::npos && line.substr(0, pos) == "target_temperature") {
            std::string_view targetTemperatureStrView = { line.data() + pos + 1 };

            ApplicationState applicationState = parseTemperature(targetTemperatureStrView);
            if (applicationState == ApplicationState::Success)
                targetTemperature = std::stod(targetTemperatureStrView.data());

            return applicationState;
        }
        else {
            return ApplicationState::IncorrectConfigParameter;
        }
    }
    else {
        return ApplicationState::ConfigFileIsNotOpen;
    }
}