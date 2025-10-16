#include "MosquittoClientWrapper.h"
#include "TemperatureLogic.h"
#include "AlarmTemperatureValidator.h"
#include "Controller.h"
#include "Utils.h"
#include <mosquitto.h>
//#include <cstdio>
//#include <string>
#include <iostream>
#include <memory>
//#include <csignal>
#include <iomanip>

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

int main() {
//    std::signal(SIGINT, signal_handler);  // Обработка Ctrl+C
//    std::signal(SIGTERM, signal_handler); // Обработка сигнала завершения

    double targetTemperature = 0.0;
    ApplicationState applicationState = readTargetTemperature(TEMPERATURE_FILE.data(), targetTemperature);

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