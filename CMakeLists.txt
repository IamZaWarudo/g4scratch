

cmake_minimum_required(VERSION 3.16)

project(g4scratch)

if(APPLE)
  message("Building for Darwin")
  add_compile_definitions(__DARWIN__=TRUE)
elseif(LINUX)
  message("Building for Linux")
  add_compile_definitions(__LINUX__=TRUE)
endif()

find_package(Geant4 REQUIRED)
find_package(ROOT REQUIRED)

set (CMAKE_CXX_STANDARD ${ROOT_CXX_STANDARD})
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

#setting output paths in the build directory
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(SIM_SOURCES
    src/Materials.cxx
    src/MyRunManager.cxx
    src/ExperimentalHall.cxx
    src/MyDetectorConstruction.cxx
    src/MySensitiveDetector.cxx
    src/ExperimentConstruction.cxx
    src/MyOutputManager.cxx
    src/Target.cxx
)


add_executable(basic src/basic.cxx ${SIM_SOURCES})

target_include_directories(basic PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${ROOT_INCLUDE_DIRS}
)

target_link_libraries(basic PRIVATE
  ${Geant4_LIBRARIES} 
  ${ROOT_LIBRARIES}
)
