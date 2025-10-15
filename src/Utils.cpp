#include "Utils.h"

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