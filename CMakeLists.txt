cmake_minimum_required(VERSION 3.12)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_SHARED_LIBRARY_PREFIX_CXX "")

project(qtm-calc)

find_package(Boost)
if(Boost_FOUND) 
  include_directories(${Boost_INCLUDE_DIRS})
  link_libraries(${Boost_LIBRARIES})

  # ====================================================================================
  #                                qtm-calc target - json
  # ====================================================================================
  add_executable(qtm-calc)
  
  target_sources(qtm-calc PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/src/qtm-core.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qtm-data.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/src/qtm-json.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
  )


  # ====================================================================================
  #                         pyqtmcalc target - python pybind11
  # ====================================================================================
  add_subdirectory(extern/pybind11)
  pybind11_add_module(pyqtmcalc)

  target_sources(pyqtmcalc PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/src/qtm-core.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qtm-data.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/main_export.cpp
  )

  target_compile_definitions(pyqtmcalc PRIVATE _LIBQTMCALC_ENABLE_PYBIND11_EXPORT)


  # ====================================================================================
  #                         libqtmcalc target - default shared 
  # ====================================================================================
  add_library(libqtmcalc SHARED)

  target_sources(libqtmcalc PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/src/qtm-core.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/qtm-data.cpp
  )
  
  target_include_directories(libqtmcalc PUBLIC ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_LIST_DIR}/src)
endif()
