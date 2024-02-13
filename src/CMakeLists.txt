add_subdirectory(pgm)
add_subdirectory(camera_handler)

add_executable(main
    main.c
)

target_link_libraries(main PUBLIC
    pgm
)


# Utility to convert rawbinary image data into pgm files.
add_executable(rawtopgm
    rawtopgm.c
)

target_link_libraries(rawtopgm PUBLIC
    pgm
)


# The example CPP code for calibration
add_executable(calibrationExample
    calibrationExample.cpp    
)

target_include_directories(calibrationExample PUBLIC
    ${PROJECT_SOURCE_DIR}/inc
)

target_link_libraries(calibrationExample PUBLIC
    pthread
    usb-1.0 
    DALProxy1280_12USB
)


# The example CPP code for the camera 
add_executable(exampleSmartIR
    exampleSmartIR.cpp    
)

target_link_libraries(exampleSmartIR PUBLIC
    pthread
    usb-1.0 
    DALProxy1280_12USB
)


