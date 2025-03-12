cmake_minimum_required(VERSION 3.10)

project(he_sensor)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_COMPILER gcc)

include_directories(src)

set(SOURCES
  src/main.c
)

add_executable(he_sensor ${SOURCES})
