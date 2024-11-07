cmake_minimum_required(VERSION 3.16)

project(test_lib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(REPOSITORY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../)
include(${REPOSITORY_DIR}/dependencies.cmake)

add_library(robot_driver_coppeliasim_panda
           ${REPOSITORY_DIR}/include/robot_driver_coppeliasim_panda.h
           ${REPOSITORY_DIR}/src/robot_driver_coppeliasim_panda.cpp)
target_link_libraries(robot_driver_coppeliasim_panda robot_driver_coppeliasim)

##########################################################
set(USE_CAPY_DQROBOTICS false) #optional
include(FetchContent)
FetchContent_Declare(capybara
    GIT_REPOSITORY https://github.com/juanjqo/capybara_toolkit
    SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/capybara
    GIT_TAG main
)
FetchContent_MakeAvailable(capybara)
set (CAPYBARA_DIR ${capybara_SOURCE_DIR})
include(${capybara_SOURCE_DIR}/capybara_library.cmake)
##########################################################

include_directories(${REPOSITORY_DIR}/include/)

add_executable(test_lib main.cpp)

target_link_libraries(test_lib capybara dqrobotics robot_driver_coppeliasim robot_driver_coppeliasim_panda)
