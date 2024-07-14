cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(artemis-ws)


list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Default installation dir
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/local/ CACHE PATH "install dir" FORCE)

find_package(PkgConfig REQUIRED)

find_package(artemis HINTS ${TARTSYS} REQUIRED)

find_package(ROOT REQUIRED COMPONENTS RIO Net Physics Minuit Minuit2 Geom Gui Genetic)
find_package(yaml-cpp REQUIRED HINTS ${ARTEMIS_YAML_CPP_LIB_DIR}/../)

option(USE_GETDECODER "option to build with GETDecoder" OFF)

pkg_check_modules(REDIS redis++)
pkg_check_modules(HIREDIS hiredis)
if (REDIS_FOUND AND HIREDIS_FOUND)
  add_compile_definitions(HAVE_REDIS_H)
  include_directories(${REDIS_INCLUDE_DIR})
  link_directories(${REDIS_LIBRARY_DIRS})

  message(STATUS "redis++ and hiredis is found")
  message(STATUS ${REDIS_LIBRARY_DIRS})
  message(STATUS ${HIREDIS_LIBRARY_DIRS})
endif()


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(${ROOT_USE_FILE})

add_subdirectory(src)






