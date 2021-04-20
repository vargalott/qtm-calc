cmake_minimum_required(VERSION 3.20)

project(qtm-calc)

# all project targets
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})

# Boost unit tests
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/tests)
