# The pgm module tests
list(APPEND TEST_LIBS "${CMOCKA_LIBRARIES}")
list(APPEND TEST_LIBS pgm)

list(APPEND TEST_DIRS "${CMOCKA_INCLUDE_DIRS}")
list(APPEND TEST_DIRS "${MyProject_SOURCE_DIR}/src")

add_cmocka_test(test_pgm
                SOURCES test_pgm.c
                COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
                LINK_LIBRARIES "${TEST_LIBS}")
add_cmocka_test_environment(test_pgm)
target_include_directories(test_pgm PUBLIC "${TEST_DIRS}")

