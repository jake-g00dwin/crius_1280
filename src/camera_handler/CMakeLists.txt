add_library(camera_test_wrap SHARED 
    camera_test_wrap.c
)

add_library(camera_handler SHARED 
    camera_handler.c
)


if(UNIT_TESTING)
    
    # ############################# 
    # Settings for the mocked lib
    # ############################# 
    include_directories(
        ${CMAKE_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMOCKA_PUBLIC_INCLUDE_DIRS}
    )

    set(WRAPPED_FUNCS = "")
    list(APPEND WRAPPED_FUNCS 
    "Proxy1280_12USB_DisconnectFromModule"
	"Proxy1280_12USB_DisconnectFromModule"
	"Proxy1280_12USB_GetErrorString"
	"Proxy1280_12USB_ConnectToModule"
	"Proxy1280_12USB_GetModuleCount"
	"Proxy1280_12USB_GetModuleName"
	"Proxy1280_12USB_GetImage"
	"Proxy1280_12USB_IsConnectToModule"
	"Proxy1280_12USB_SetNUCProcessing"
	"Proxy1280_12USB_SetShutterLessProcessing"
	"Proxy1280_12USB_SetAGCProcessing"
	"Proxy1280_12USB_SetFloatFeature"
	"Proxy1280_12USB_InitShutter2PtsCalibration"
	"Proxy1280_12USB_StepShutter2PtsCalibration"
	"Proxy1280_12USB_FinishShutter2PtsCalibration"
	"test_mock"
    )
    set(WRAPPED_STR = "")
    list(JOIN WRAPPED_FUNCS ", --wrap=" WRAPPED_STR)
    message("WRAPPED_STR: " ${WRAPPED_STR})

    set_target_properties(cam_test_wrap
            PROPERTIES
            LINK_FLAGS  "-Wl${WRAPPED_STR}"
    )

    target_link_libraries(camera_test_wrap PUBLIC
            cmocka::cmocka
    )


    target_link_libraries(camera_handler PUBLIC
        camera_test_wrap
    )


else()

    target_include_directories(camera_handler PUBLIC
        ${PROJECT_SOURCE_DIR}/camera_sdk/
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    set_target_properties(camera_handler PROPERTIES VERSION 1.0 SOVERSION 1)
    
    if(MSVC OR MSYS OR MINGW)
        add_compile_definitions(DLL_EXPORTS)
        find_library(DALProxy1280_12USB_x64
            NAMES DALProxy1280_12USB_x64.dll DALProxy1280_12USB_x64.lib
            HINTS ${PROJECT_SOURCE_DIR}/camera_sdk/windows_x86/
            NO_DEFAULT_PATH
            NO_SYSTEM_ENVIRONMENT_PATH
        )
        

    else()
    LINK_DIRECTORIES(
        ${PROJECT_SOURCE_DIR}/camera_sdk/linux_armv8hf/
    )
    target_link_libraries(camera_handler PUBLIC
        DALProxy1280_12USB
        usb-1.0
    )
    endif()

endif()


