# Crius 1280 Camera Software

## Project Usage


## Project structure:


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


