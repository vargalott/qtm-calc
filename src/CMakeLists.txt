cmake_minimum_required(VERSION 3.20)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SHARED_LIBRARY_PREFIX_CXX "")

find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)

  # inner subfolders with necessary header files (exscepting json.dir)
  set(INNER_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/core ${CMAKE_CURRENT_SOURCE_DIR}/data)

  # ====================================================================================
  #                                qtm-calc target - json
  # ====================================================================================
  add_executable(qtm-calc)

  target_sources(qtm-calc PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/core/qtm-core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/data/qtm-data.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/json/qtm-json.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  )

  # json.dir explicitly
  target_include_directories(qtm-calc PRIVATE ${INNER_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/json ${Boost_INCLUDE_DIRS})
  target_link_libraries(qtm-calc PRIVATE ${Boost_LIBRARIES})


  # ====================================================================================
  #                         pyqtmcalc target - python pybind11
  # ====================================================================================
  # probably bad idea
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../extern/pybind11 ${CMAKE_CURRENT_BINARY_DIR}/pybind11)
  pybind11_add_module(pyqtmcalc)

  target_sources(pyqtmcalc PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/core/qtm-core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/data/qtm-data.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pyqtmcalc.cpp
  )

  target_compile_definitions(pyqtmcalc PRIVATE _PYQTMCALC_ENABLE_PYBIND11_EXPORT)
  target_include_directories(pyqtmcalc PRIVATE ${INNER_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
  target_link_libraries(pyqtmcalc PRIVATE ${Boost_LIBRARIES})


  # ====================================================================================
  #                         libqtmcalc target - default shared 
  # ====================================================================================
  add_library(libqtmcalc SHARED)

  target_sources(libqtmcalc PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/core/qtm-core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/data/qtm-data.cpp
  )

  target_include_directories(libqtmcalc PUBLIC ${INNER_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
  target_link_libraries(libqtmcalc PRIVATE ${Boost_LIBRARIES})

endif()
