#include "ApplicationState.h"
#include "Utils.h"
#include <catch2/catch_all.hpp>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

constexpr const char* CURRENT_SOURCE_FILE_PATH = __FILE__;

constexpr const char* RESOURCE_FOLDER = "resource";

constexpr const char* WRONG_CONFIG_FILE = "target_temperature.ini";
constexpr const char* WRONG_CONFIG_PARAMETER_FILE = "wrong_config_parameter.conf";
constexpr const char* NOT_REAL_NUMBER_FILE = "not_real_number.conf";
constexpr const char* OUT_OF_LENGTH_RANGE_FILE = "config_parameter_out_of_length_range.conf";
constexpr const char* INCORRECT_VALUE_FILE = "incorrect_real_part.conf";
constexpr const char* CORRECT_VALUE_FILE = "correct_value.conf";

TEST_CASE("ReadTargetTemperature", "[LibmosquittoTest]") {
    auto testOpenFileResourcePath = fs::path(CURRENT_SOURCE_FILE_PATH).parent_path().append(RESOURCE_FOLDER);
    double targetTemperature = 0.0;
    std::string filename;

    SECTION("IncorrectConfigFileName") {
        filename = testOpenFileResourcePath.append(WRONG_CONFIG_FILE).string();

        REQUIRE(readTargetTemperature(filename, targetTemperature) == ApplicationState::ConfigFileIsNotOpen);
    }

    SECTION("IncorrectConfigParameterName") {
        filename = testOpenFileResourcePath.append(WRONG_CONFIG_PARAMETER_FILE).string();

        REQUIRE(readTargetTemperature(filename, targetTemperature) == ApplicationState::IncorrectConfigParameter);
    }

    SECTION("ConfigParameterIsNotRealNumber") {
        filename = testOpenFileResourcePath.append(NOT_REAL_NUMBER_FILE).string();

        REQUIRE(readTargetTemperature(filename, targetTemperature) == ApplicationState::TemperatureIsNotRealValue);
    }

    SECTION("ConfigParameterOutOfLengthRange") {
        filename = testOpenFileResourcePath.append(OUT_OF_LENGTH_RANGE_FILE).string();

        REQUIRE(readTargetTemperature(filename, targetTemperature) == ApplicationState::IncorrectTemperatureLength);
    }

    SECTION("IncorrectTemperatureValue") {
        filename = testOpenFileResourcePath.append(INCORRECT_VALUE_FILE).string();

        REQUIRE(readTargetTemperature(filename, targetTemperature) == ApplicationState::IncorrectTemperature);
    }

    SECTION("CorrectTemperatureValue") {
        filename = testOpenFileResourcePath.append(CORRECT_VALUE_FILE).string();

        REQUIRE(readTargetTemperature(filename, targetTemperature) == ApplicationState::Success);
    }
}