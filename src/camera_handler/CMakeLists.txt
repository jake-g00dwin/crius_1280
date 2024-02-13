add_library(camera_handler SHARED 
    camera_handler.c
    camera_handler.h
)

LINK_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}/camera_sdk
)

target_include_directories(camera_handler PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(camera_handler  PUBLIC
    DALProxy1280_12USB
    usb-1.0 
    pgm
    pthread
)



