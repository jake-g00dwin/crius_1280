# Crius 1280 Camera Software

## Project Usage

### Downloading the Pre-compiled Binaries



### Building for usage


To build the shared library of C code that allows interfacing with python
follow the below prompts.

This assumes that the required SDK shared libraries are either installed 
system wide or the repo's included ones are used. By default the ones in the
`camera_sdk` directory are used.

The build process handles the OS/toolchains by itself automatiaclly for all
supported platforms.

```sh
git clone https://github.com/jake-g00dwin/crius_1280.git
cd crius_1280
cd build
cmake ../
make camera_handler
```



### Running the Python program

The repo comes included with the needed python script to show the usage of
the shared C library.

If you have an existing python3 installation ensure you have the required
dependencies installed.

You can do this through the `src/pyprog/requirements.txt` file and pip using the 
commands listed below for linux or WSL(Windows subsystem for linux).
```sh
cd ./src/pyprog/
python3 -m pip install -r ./requirements.txt
```

To run the program using the shared libraries that are required:

**UNIX:**
```sh
# Use the global library path if installed there.
sudo LD_LBIRARY_PATH=/lib/crius/ python3 ./cam.py

# Use the repo's files if needed
sudo LD_LBIRARY_PATH=../../camera_sdk/ python3 ./cam.py
```

**Windows:**





## Project structure:

**Overview:**
```sh
tree -L 1 ./
./
├── aarch64_toolchain.cmake
├── build
├── camera_sdk
├── cmake
├── CMakeLists.txt
├── docs
├── inc
├── README.md
├── setup.sh
├── src
├── tdd.sh
├── tests
7 directories, 6 files
```
The project is layed out with all the source code inside the `src/` 
subdirectory. Additional modules that are defined are contained in additional
directories along with their header files.

The acompaning tests are located inside `tests/` in the project's root 
directory.

To change the settings when the project is being built the `CMakeLists.txt`
file in the project root would need to be edited.


## Testing

The testing for the project now features a interactive menu inside the 
`tdd.sh` script for all posix/unix systems with `sh` shells availble.

To actually run the tests simply follow the prompts.

```sh
~: ./tdd.sh
BUILD MENU:
1. C Tests for camera_handler
2. Pytest for camera_handler
3. build for release
4. Reserved
5. Exit
Enter your choice: 5 
Exiting...
```

### Pytest

The python code tests depend on the shared library of the camera_handler 
being built. The code accesses the shared library via a pointer in the 
`src/pyprog/shared/` sub-directory.

Before attempting to run pytest you should first select the option for pytest
while running the `tdd.sh` file in the projects root directory.

