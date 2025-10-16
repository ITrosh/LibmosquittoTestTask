set(TEST_TARGET LibmosquittoTest)

set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/src/Utils.cpp
    ${CMAKE_SOURCE_DIR}/src/ApplicationState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LibmosquittoTest.cpp
)

add_executable(${TEST_TARGET} ${TEST_SOURCES})

target_include_directories(${TEST_TARGET} PUBLIC
    ${CMAKE_SOURCE_DIR}/inc/
)

target_link_libraries(${TEST_TARGET} PRIVATE Catch2::Catch2WithMain)