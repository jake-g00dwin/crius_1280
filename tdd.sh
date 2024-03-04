#!/bin/sh

CROSS_TC="$(pwd)/aarch64_toolchain.cmake"
CROSS_TC_WIN="$(pwd)/i686-w64-mingw32_toolchain.cmake"
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


build_camera_handler () {
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

build_release() {
    clear_cmake_cache 
    cmake -DCAM_HANDLER_LIB=ON -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE} ../ 
    make camera_handler
}

build_windows_release() {
    clear_cmake_cache
    cmake  -DCMAKE_TOOLCHAIN_FILE=${CROSS_TC_WIN} -DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE} ../ 
    make camera_handler
}

package_release() {
    PTH="../windows_builds"
    F="crius_1280_vx-x-x"
    mkdir $PTH/$F 
    mkdir $PTH/$F/shared

    cp ./src/cam.py $PTH/$F
    cp ./src/demo.py $PTH/$F

    zip "${PTH}/${F}.zip" "${PTH}/${F}"
}

build_pytest () {
    # Builds the project so that pytest can run.
    cp ./src/camera_handler/testdata.bin /tmp/
    clear_cmake_cache
    cmake -DUNIT_TESTING=ON  -DCMAKE_VERBOSE_MAKEFILE=ON -DPYTEST=ON ../
    make camera_test_wrap && make camera_handler 
}

run_c_tests () {
    cp ./src/camera_handler/testdata.bin /tmp/
    clear_cmake_cache
    cmake -DUNIT_TESTING=ON  -DCMAKE_VERBOSE_MAKEFILE=ON ../
    make camera_handler && make test_camera_handler && ./tests/camera_handler/test_camera_handler
}


menu () {
    valid_choice=false

    while [ "$valid_choice" != true ]; do
        echo "BUILD MENU:"
        echo "1. C Tests for camera_handler"
        echo "2. Pytest for camera_handler"
        echo "3. build for release"
        echo "4. cross compile for windows"
        echo "5. Exit"

        read -p "Enter your choice: " choice

        case $choice in
            1)
                echo "You selected Option 1"
                valid_choice=true
                run_c_tests
                ;;
            2)
                echo "You selected Option 2"
                valid_choice=true
                build_pytest
                ;;
            3)
                echo "You selected Option 3"
                valid_choice=true
                build_release
                ;;
            4)
                echo "You selected Option 4"
                valid_choice=true
                build_windows_release
                ;;
            5)
                echo "Exiting..."
                exit 0
                ;;
            *)
                echo "Invalid choice. Please select a valid option."
                ;;
        esac
    done
}

menu
