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


build_main () {
    clear_cmake_cache
    
    cmake -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE} ../
    make main
}

build_main_test () {
    clear_cmake_cache
    
    cmake -DUNIT_TESTING=1 ../
    ctest
}


build_pgm_test ()  {
    clear_cmake_cache
    cmake -DUNIT_TESTING=1 ../
    ctest
}

build_pgm_test
#build_calibration_example 
