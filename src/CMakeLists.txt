add_subdirectory(pgm)
add_subdirectory(camera_handler)

add_executable(main
    main.c
)
target_link_libraries(main PUBLIC
    pgm
)

add_executable(calibrationExample
    calibrationExample.cpp    
)

target_include_directories(calibrationExample PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
)

target_link_libraries(calibrationExample PUBLIC
    DALProxy1280_12USB
    usb-1.0 
    pthread
)

add_executable(exampleSmartIR
    exampleSmartIR.cpp    
)


