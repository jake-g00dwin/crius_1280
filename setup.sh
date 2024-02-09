#!/bin/sh

# Filename: setup.sh
# Description: Helps to setup the needed development packages.


install_software () {
    echo "Installing needed dependencies..."
    sudo apt install build-essential
    sudo apt install cmake
    sudo apt install make
    sudo apt install git
}

# Installs the CXX(cpp) unit testing framework
install_cpputest () {
    sudo apt install cpputest
}

# Builds and installs CMocka the unit testing harness.
install_cmocka () {
    echo "Downloading CMOCKA unit testing harness..."
    git clone https://git.cryptomilk.org/projects/cmocka.git
    cd cmocka
    echo "Building CMOCKA..."
    cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug
    cmake --build build
    echo "cmocka should be ready now."
}



install_software
#install_cpputest
install_cmocka

