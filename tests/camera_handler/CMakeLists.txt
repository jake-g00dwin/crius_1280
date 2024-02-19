# The camera_handler module tests
list(APPEND TEST_LIBS "${CMOCKA_LIBRARIES}")
list(APPEND TEST_LIBS camera_handler)
#list(APPEND TEST_LIBS camera_test_wrap)

list(APPEND TEST_DIRS "${CMOCKA_INCLUDE_DIRS}")
list(APPEND TEST_DIRS "${PROJECT_SOURCE_DIR}/src")

add_cmocka_test(test_camera_handler
                SOURCES test_camera_handler.c 
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${TEST_LIBS}")
add_cmocka_test_environment(test_camera_handler)
target_include_directories(test_camera_handler PUBLIC "${TEST_DIRS}")

