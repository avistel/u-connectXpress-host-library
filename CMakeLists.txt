cmake_minimum_required(VERSION 3.10)

# set the project name
project(uconnectxpress_host_library)

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

# add the library
add_library(uchx ${SOURCES})
add_link_options(uchx -mconsole)
