mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --target thermostat_controller thermostat_device LibmosquittoTest