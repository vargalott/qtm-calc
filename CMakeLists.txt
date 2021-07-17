cmake_minimum_required(VERSION 3.20)

project(qtm-calc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS system unit_test_framework)
if(Boost_FOUND)

  # ====================================================================================
  #                                qtm-calc target - json
  # ====================================================================================
  add_executable(qtm-calc)

  target_sources(qtm-calc
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/core.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/data.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/json.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  )

  target_include_directories(qtm-calc
    PRIVATE
      ${Boost_INCLUDE_DIRS}
      ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(qtm-calc
    PRIVATE
      ${Boost_LIBRARIES}
  )


  # ====================================================================================
  #                         pyqtmcalc target - python pybind11
  # ====================================================================================
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extern/pybind11)
  pybind11_add_module(pyqtmcalc)

  target_sources(pyqtmcalc
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/src/core.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/data.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/pyqtmcalc.exp.cpp
  )

  target_compile_definitions(pyqtmcalc PRIVATE _PYQTMCALC_ENABLE_PYBIND11_EXPORT)
  target_include_directories(pyqtmcalc
    PRIVATE
      ${Boost_INCLUDE_DIRS}
      ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(pyqtmcalc
    PRIVATE
      ${Boost_LIBRARIES}
  )

  # ====================================================================================
  #                                  boost tests target
  # ====================================================================================

  add_executable(boost_tests EXCLUDE_FROM_ALL)

  target_sources(boost_tests
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/tests/entry.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/core.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/src/data.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_suite_core.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_suite_data.cpp
  )
  target_include_directories(boost_tests
    PRIVATE
      ${Boost_INCLUDE_DIRS}
      ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  target_link_libraries(boost_tests
    PRIVATE
      ${Boost_LIBRARIES}
  )

  add_custom_target(run-tests COMMAND $<TARGET_FILE:boost_tests> -l all -r short)
  add_dependencies(run-tests boost_tests)

endif()
