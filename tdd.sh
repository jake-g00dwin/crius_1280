#!/bin/sh

CROSS_TC="$(pwd)/aarch64_toolchain.cmake"
CMAKE_VERBOSE="ON"
CROSS_COMPILE=1

echo $CROSS_TC

clear_cmake_cache () {
    cd ./build
    rm -rf CMakeCache.txt CMakeFiles/
}

build_calibration_example () {
    clear_cmake_cache
    
    cmake -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE} -DCMAKE_TOOLCHAIN_FILE=${CROSS_TC} ../
    make calibrationExample
}

build_example_smart_ir () {
    clear_cmake_cache
    
    cmake -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE}  -DCMAKE_TOOLCHAIN_FILE=${CROSS_TC} ../
    make calibrationExample
}


build_camer_handler () {
    clear_cmake_cache
    
    cmake -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE}  -DCMAKE_TOOLCHAIN_FILE=${CROSS_TC} ../
    make camera_handler
    ldd ./src/camera_handler/libcamera_handler.so 
}


build_main () {
    clear_cmake_cache
    
    cmake -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE} ../
    make main
}



run_tests ()  {
    #copy the needed data file for the tests to the /tmp dir.
    #This is required for the tests of the shared libs to work correctly.
    cp ./src/camera_handler/testdata.bin /tmp/

    clear_cmake_cache
    cmake -DUNIT_TESTING=ON ../
    

    #make simple_test
    #make pgm && make test_pgm
    make camera_handler && make test_camera_handler
    #ctest 
    ./tests/camera_handler/test_camera_handler
}



run_tests
#build_calibration_example 

