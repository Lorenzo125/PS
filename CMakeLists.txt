cmake_minimum_required(VERSION 2.8.9)
project(PSMin)

find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_CXX_FLAGS "-O3 -std=c++14")

include_directories(include)
file(GLOB SOURCES "src/*.cc")

project(examplePerceptronMultiLayer)
add_executable(PSMin ${SOURCES})
target_link_libraries(PSMin ${ROOT_LIBRARIES})
