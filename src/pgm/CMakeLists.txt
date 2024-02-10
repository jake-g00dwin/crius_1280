add_library(pgm STATIC
    pgm.c
)

target_include_directories(pgm PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
