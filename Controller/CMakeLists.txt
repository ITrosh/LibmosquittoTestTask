cmake_minimum_required(VERSION 3.20)
project(thermostat_controller)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/src/Utils.cpp
    ${CMAKE_SOURCE_DIR}/src/ApplicationState.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TemperatureLogic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/AlarmTemperatureValidator.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/
)

#add_library(mosquitto SHARED IMPORTED)
#
#set_target_properties(mosquitto PROPERTIES IMPORTED_IMPLIB "C:/Program Files/mosquitto/devel/mosquitto.lib")

#set_target_properties(mosquitto PROPERTIES IMPORTED_LOCATION ${MOSQUITTO_LIB})

# Link the Mosquitto library to target
target_link_libraries(${PROJECT_NAME} PRIVATE ${MOSQUITTO_LIB} nlohmann_json::nlohmann_json)
