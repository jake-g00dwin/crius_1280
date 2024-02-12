add_library(camera_handler STATIC
    camera_handler.c
)

target_include_directories(camera_handler PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
