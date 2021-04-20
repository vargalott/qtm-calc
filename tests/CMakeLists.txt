cmake_minimum_required(VERSION 3.20)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
if(Boost_FOUND)

  add_executable(tests)

  # target_sources(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
  target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(tests PRIVATE ${Boost_LIBRARIES})

endif()
