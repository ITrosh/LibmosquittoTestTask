cmake_minimum_required(VERSION 3.20)
project(LibmosquittoTestTask)

include(FetchContent)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.11.0
)

FetchContent_MakeAvailable(json)
FetchContent_MakeAvailable(Catch2)

find_path(MOSQUITTO_INCLUDE_DIR mosquitto.h)
message(STATUS "Mosquitto include dir: ${MOSQUITTO_INCLUDE_DIR}")
find_library(MOSQUITTO_LIB mosquitto)
message(STATUS "Mosquitto lib: ${MOSQUITTO_LIB}")

add_subdirectory(Device)
add_subdirectory(Controller)
add_subdirectory(test)