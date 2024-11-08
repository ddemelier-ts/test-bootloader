cmake_minimum_required(VERSION 3.28)

set(BOARD "nrf54l15pdk/nrf54l15/cpuapp")
set(BOARD_ROOT ${CMAKE_SOURCE_DIR})
set(NO_BUILD_TYPE_WARNING On)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blink)

target_sources(app PRIVATE main.c)