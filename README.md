# Crius 1280 Camera Software

## Project Usage

### Building for usage

To build the shared library of C code that allows interfacing with python
follow the below prompts.

This assumes that the required SDK shared libraries are either installed 
system wide or the repo's included ones are used.

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

```sh
# Use the global library path if installed there.
sudo LD_LBIRARY_PATH=/lib/crius/ python3.8 ./cam.py

# Use the repo's files if needed
sudo LD_LBIRARY_PATH=../../camera_sdk/ python3.8 ./cam.py
```


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

