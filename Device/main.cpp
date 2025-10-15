#include "Sensor.h"
#include "Utils.h"
#include <mosquitto.h>
#include <memory>
//#include <csignal>

constexpr size_t NUMBER_OF_ARGUMENTS = 3;
constexpr std::string_view CMD_LINE_SECOND_ARGUMENT = "--set-alarm-temp";

int main(int argc, char** argv) {
//    std::signal(SIGINT, signal_handler);  // Обработка Ctrl+C
//    std::signal(SIGTERM, signal_handler); // Обработка сигнала завершения

    ApplicationState applicationState = ApplicationState::Success;

    if (argc == NUMBER_OF_ARGUMENTS) {
        if (argv[argc - 2] == CMD_LINE_SECOND_ARGUMENT) {
            std::string_view alarmTemperatureStrView = {argv[argc - 1]};

            applicationState = parseTemperature(alarmTemperatureStrView);
            if (applicationState == ApplicationState::Success) {
                int rc = mosquitto_lib_init();
                if (rc == MOSQ_ERR_SUCCESS) {
                    try {
                        // Create a shared_ptr to the MosquittoClientWrapper
                        auto mosq_shared_ptr = std::make_shared<MosquittoClientWrapper>(
                                "thermostat_device" // Arguments for mosquitto_new
                        );

                        Sensor sensor(std::stod(argv[argc - 1]), mosq_shared_ptr);
                        sensor.run();
                    }
                    catch (const std::invalid_argument &e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                        applicationState = ApplicationState::AlarmTemperatureIsNotNumber;
                    }
                    catch (const std::runtime_error &e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                        applicationState = ApplicationState::InvalidConnectToMQTTBroker;
                    }
                    catch (...) {
                        std::cerr << "Unhandled exception!" << std::endl;
                        applicationState = ApplicationState::UnhandledException;
                    }

                    mosquitto_lib_cleanup();
                }
                else {
                    applicationState = ApplicationState::InitLibmosquittoFailed;
                }
            }
            else {
                applicationState = ApplicationState::ParsingAlarmTemperatureFailed;
            }
        }
        else {
            applicationState = ApplicationState::IncorrectSecondArgument;
        }
    }
    else {
        applicationState = ApplicationState::IncorrectNumberOfArguments;
    }

    printApplicationState(applicationState);
    return static_cast<int>(applicationState);
}