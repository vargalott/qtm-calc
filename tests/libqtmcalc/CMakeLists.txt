cmake_minimum_required(VERSION 3.20)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED COMPONENTS unit_test_framework)
if(Boost_FOUND)

  add_executable(libqtmcalc_boost_tests)
  add_dependencies(libqtmcalc_boost_tests libqtmcalc)

  target_sources(libqtmcalc_boost_tests PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/entry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_suite_core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/test_suite_data.cpp
  )
  target_include_directories(libqtmcalc_boost_tests PRIVATE ${Boost_INCLUDE_DIRS})
  target_link_libraries(libqtmcalc_boost_tests PRIVATE ${Boost_LIBRARIES} libqtmcalc)

  add_custom_target(run-tests COMMAND $<TARGET_FILE:libqtmcalc_boost_tests> -l all -r short)

endif()
