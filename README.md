# Crius 1280 Camera Software

## Project Usage

### Image Outputs

At the moment to reduce the processing time needed for each image/frame the 
incoming data in the form of uint16_t for each pixel will be encoded into the
PGM format.

This format requires minimal processing time and is lossless for 16bit pixel
values.

Image outputs at the moment are setup to default to the systems `/tmp/` 
directory for speed and to reduce the R/W cycles on the slower storage
mediums that may also have lower endurance such as uSD cards.


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


## Running Tests

The command below shows how to run the tests for a development machine with 
the correct enviroment setup.

```sh
./tdd.sh

```

The script is setup to automatically enter the build directory, run cmake,
make the correct dependencies and run the tests.

If you want to try running tests manually you can do so by passing a flag to 
the CMake build system like so:

```sh
cd ./build
cmake -DUNIT_TESTING=ON ../
make all
ctest
```

Keep in mind it may cause dependency conflicts by running `make all` during
tests.

