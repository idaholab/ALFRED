# Copyright 2025, Battelle Energy Alliance, LLC, ALL RIGHTS RESERVED
cmake_minimum_required(VERSION 3.16...3.27)
project(geant4_ALFRED)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include  ${Geant4_INCLUDE_DIR})

file(GLOB sources ${PROJECT_SOURCE_DIR}/sources/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(alfred ${PROJECT_SOURCE_DIR}/main.cc ${sources} ${headers})
target_link_libraries(alfred ${Geant4_LIBRARIES})

add_custom_target(geant4_ALFRED DEPENDS alfred)