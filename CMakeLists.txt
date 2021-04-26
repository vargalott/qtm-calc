cmake_minimum_required(VERSION 3.20)

project(qtm-calc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# all project targets
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})

# Boost libqtmcalc unit tests
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests/libqtmcalc EXCLUDE_FROM_ALL)
