#include "MosquittoClientWrapper.h"
#include "TemperatureLogic.h"
#include "AlarmTemperatureValidator.h"
#include "Controller.h"
#include "Utils.h"
#include <mosquitto.h>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <memory>
//#include <csignal>
#include <iomanip>

constexpr std::string_view TEMPERATURE_FILE = "../../Controller/resource/target_temperature.conf";

//void on_connect(struct mosquitto* mosq, void* obj, int rc) {
//    printf("ID: %d\n", * (int*) obj);
//    if (rc) {
//        printf("Error with result code: %d\n", rc);
//        std::exit(-1);
//    }
//
//    mosquitto_subscribe(mosq, nullptr, "test/t1", 0);
//}
//
//void on_message(struct mosquitto* mosq, void* obj, const struct mosquitto_message* msg) {
//    printf("New message with topic %s: %s\n", msg->topic, (char *) msg->payload);
//}

ApplicationState readTargetTemperature(double& targetTemperature);

int main() {
//    std::signal(SIGINT, signal_handler);  // Обработка Ctrl+C
//    std::signal(SIGTERM, signal_handler); // Обработка сигнала завершения

    double targetTemperature = 0.0;
    ApplicationState applicationState = readTargetTemperature(targetTemperature);

    if (applicationState == ApplicationState::Success) {
        std::cout << "Target temperature: " << std::fixed << std::setprecision(1) << targetTemperature << std::endl;
        int rc = mosquitto_lib_init();

        if (rc == MOSQ_ERR_SUCCESS) {
            try {
                // Create a shared_ptr to the MosquittoClientWrapper
                auto mosq_shared_ptr = std::make_shared<MosquittoClientWrapper>(
                        "thermostat_controller" // Arguments for mosquitto_new
                );

                TemperatureLogic::setData(targetTemperature, mosq_shared_ptr);
                AlarmTemperatureValidator::setData(mosq_shared_ptr);

                Controller controller(mosq_shared_ptr);
                controller.run();
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

    printApplicationState(applicationState);
    return static_cast<int>(applicationState);
}

ApplicationState readTargetTemperature(double& targetTemperature) {
    std::ifstream file(TEMPERATURE_FILE.data());

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