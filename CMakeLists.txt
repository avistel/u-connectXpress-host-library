cmake_minimum_required(VERSION 3.10)

# set the project name
project(uconnectxpress_host_library)
include(Ctest)
include_directories(include)

set(SOURCES
    src/cb_at_util.c
    src/cb_string.c
    src/cb_tokenizer.c
    src/ucxh_edm.c
    src/ucxh_edm_parser.c
    src/ucxh_mode.c
    src/ucxh_parser.c
    src/ucxh_poll.c
    src/ucxh_send.c
    src/ucxh_urc.c
    src/ucxh_wait.c
    src/ucxh_wifi.c)

list(APPEND src/generic/ucxh_serial_generic.c)

set(TEST_SOURCES
    test/test_datamode.c
    test/test_edm.c
    test/test_mock_ati9.c
    test/test_getsystem.c
    test/test_tokenizer.c
    test/test_edm_at.c
    test/test_getgeneral.c
    test/test_send.c
    test/test_edm_at_read.c
    test/test_at_peer.c
    test/test_at_wifi.c
    test/test_ati9.c)

enable_testing()
# add the library
#add_library(ucxh ${SOURCES})
#add_link_options(ucxh -mconsole)
foreach(FILENAME IN ITEMS ${TEST_SOURCES})
    get_filename_component(TGT_NAME ${FILENAME} NAME_WLE)
    message(DEBUG "Target name: $(TGT_NAME)")
    add_executable(${TGT_NAME} ${FILENAME} test/ucxh_serial_mock.c test/test_tools.c)
    target_compile_definitions(${TGT_NAME} PRIVATE CONFIG_USE_MOCKED_SERIAL)
    target_sources(${TGT_NAME} PRIVATE ${SOURCES})
    string(REGEX REPLACE "test_" "" CTEST_TGT_NAME ${TGT_NAME})
    add_test(${CTEST_TGT_NAME} ${TGT_NAME})
endforeach()

