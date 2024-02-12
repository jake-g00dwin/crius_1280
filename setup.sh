#!/bin/sh

# Filename: setup.sh
# Description: Helps to setup the needed development packages.


install_software () {
    echo "Installing needed dependencies..."
    sudo apt install build-essential
    sudo apt install cmake
    sudo apt install make
    sudo apt install git
    sudo apt install python3.11
    sudo apt install python3.11-venv
}

# Installs the CXX(cpp) unit testing framework
install_cpputest () {
    sudo apt install cpputest
}

# Builds and installs CMocka the unit testing harness.
install_source_cmocka () {
    echo "Downloading CMOCKA unit testing harness..."
    git clone https://git.cryptomilk.org/projects/cmocka.git
    cd cmocka
    echo "Building CMOCKA..."
    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    echo "cmocka should be ready now."
}

install_binary_cmocka () {
    echo "Installing the binary for cmocka"   
    sudo apt install cmocka-doc
    sudo apt install libcmocka0
}


# Insalls the shared library files to the system.
# This is optional as the cmake setup can just link to the local ones.
install_camera_sdk () {
    echo "Installing the pre-compiled library files..."
    cp camera_sdk/lib* /usr/lib
    
    echo "Installing the header files..."
    cp camera_sdk/*.h /usr/include
}


install_software
#install_cpputest
#install_cmocka

