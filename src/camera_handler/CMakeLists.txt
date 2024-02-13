add_library(camera_handler SHARED 
    camera_handler.c
    camera_handler.h
)

target_include_directories(camera_handler PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(camera_handler  PUBLIC
    DALProxy1280_12USB
    usb-1.0 
    pthread
)



