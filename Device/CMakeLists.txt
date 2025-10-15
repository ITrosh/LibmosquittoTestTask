cmake_minimum_required(VERSION 3.20)
project(thermostat_device)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
    ${CMAKE_SOURCE_DIR}/inc/Utils.h
    ${CMAKE_SOURCE_DIR}/src/Utils.cpp
    ${CMAKE_SOURCE_DIR}/inc/MosquittoClientWrapper.h
    ${CMAKE_SOURCE_DIR}/inc/ApplicationState.h
    ${CMAKE_SOURCE_DIR}/src/ApplicationState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sensor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Sensor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Heater.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Heater.h
)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
)

#add_library(mosquitto SHARED IMPORTED)
#
#set_target_properties(mosquitto PROPERTIES IMPORTED_IMPLIB "C:/Program Files/mosquitto/devel/mosquitto.lib")
#set_target_properties(mosquitto PROPERTIES IMPORTED_LOCATION ${MOSQUITTO_LIB})

# Link the Mosquitto library to target
target_link_libraries(${PROJECT_NAME} PRIVATE ${MOSQUITTO_LIB} nlohmann_json::nlohmann_json)
