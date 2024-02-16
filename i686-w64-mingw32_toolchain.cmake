# Specify the cross compiler
SET(CMAKE_C_COMPILER /usr/bin/i686-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/i686-w64-mingw32-gcc)
SET(CMAKE_RC_COMPILER i686-w64-mingw32-windres)
SET(CMAKE_RANLIB i686-w64-mingw32-ranlib)

#SET(target_tripple "i686-w64-mingw32")
#SET(cpu_flags "")

# Specify the target architecture
#SET(CMAKE_SYSTEM_NAME MINGW)
SET(CMAKE_SYSTEM_NAME Windows)
#SET(CMAKE_SYSTEM_PROCESSOR X86)
SET(CMAKE_SYSTEM_PROCESSOR AMD64)

# Specify the root directory of the cross-compiler toolchain
SET(CMAKE_FIND_ROOT_PATH /usr/bin/) 

# Specify the search path for libraries and headers
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

