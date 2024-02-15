add_library(camera_test_wrap SHARED
    camera_test_wrap.c
)


add_library(camera_handler SHARED 
    camera_handler.c
)

target_include_directories(camera_handler PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMOCKA_PUBLIC_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/inc
)


if(UNIT_TESTING)
    message("LINKING WITH --wrap")
    target_link_libraries(camera_handler PUBLIC
        camera_test_wrap
    )

    set_target_properties(camera_handler
            PROPERTIES
            LINK_FLAGS  "-Wl,--wrap=Proxy1280_12USB_DisconnectFromModule,--wrap=Proxy1280_12USB_DisconnectFromModule,--wrap=Proxy1280_12USB_GetErrorString,--wrap=Proxy1280_12USB_ConnectToModule,--wrap=Proxy1280_12USB_GetModuleCount,--wrap=Proxy1280_12USB_GetModuleName,--wrap=Proxy1280_12USB_GetImage,--wrap=Proxy1280_12USB_IsConnectToModule,--wrap=Proxy1280_12USB_SetNUCProcessing,--wrap=Proxy1280_12USB_SetShutterLessProcessing,--wrap=Proxy1280_12USB_SetAGCProcessing,--wrap=Proxy1280_12USB_SetFloatFeature"
    )


else()
    LINK_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/camera_sdk
    )

    target_link_libraries(camera_handler  PUBLIC
        DALProxy1280_12USB
        usb-1.0
    )
endif()


