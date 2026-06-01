

cmake_minimum_required(VERSION 3.16)
project(g4scratch)

find_package(Geant4 REQUIRED)
find_package(ROOT REQUIRED)

include(${Geant4_USE_FILE})
include(${ROOT_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cxx)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

add_executable(basic basic.cxx ${sources} ${headers})
target_link_libraries(basic ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
