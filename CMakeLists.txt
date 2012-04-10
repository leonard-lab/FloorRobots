##################################################
#
# CMakeLists.txt - Cmake file for FloorRobots
#
# History:
#   * Created from the Beluga CMakeLists file - DTS 4/10/12
#   
##################################################

# minimum required version of CMake - should be OK on
#   most modern systems
cmake_minimum_required (VERSION 2.8)

# name of the project - this has to come first
project(FloorRobots)

# MADTRaC information
set(MT_ROOT "../MADTraC/build" CACHE PATH "MADTraC root directory")
# sets variables related to MT
include(${MT_ROOT}/cmake/MT_Config.cmake)

# set the name of the built target
set(APP_NAME FloorRobots)

# set this to a list of source and header files to be compiled
set(APP_SRC
  src/FloorRobotsGUI.cpp
  src/FloorRobotsGUI.h
  # TODO: Add the rest!
)

# adds src to the header search path
include_directories(src)

# sets up the build target
add_executable(${APP_NAME} WIN32 MACOSX_BUNDLE ${APP_SRC})

# this macro (from MT_Config.cmake) sets up all of the
#   compiler and linker options automatically
MT_robot_app(${APP_NAME})
