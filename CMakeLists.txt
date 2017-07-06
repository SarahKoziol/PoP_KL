cmake_minimum_required(VERSION 3.7)
project(PoP_KL)

set(CMAKE_CXX_STANDARD 14)

SET(BUILD_SHARED_LIBRARIES OFF)
SET(CMAKE_EXE_LINKER_FLAGS "-static")

set(SOURCE_FILES main.cpp)
add_executable(PoP_KL ${SOURCE_FILES})
