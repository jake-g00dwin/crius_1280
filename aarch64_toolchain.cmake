# Specify the cross compiler
SET(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc-12)
SET(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++-12)

# Specify the target architecture
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR aarch64)

# Specify the root directory of the cross-compiler toolchain
SET(CMAKE_FIND_ROOT_PATH /usr/bin/) 

# Specify the search path for libraries and headers
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

