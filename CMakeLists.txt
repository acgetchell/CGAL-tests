cmake_minimum_required(VERSION 3.10)

project(CGAL-tests VERSION 0.1.0 LANGUAGES CXX)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(
    FATAL_ERROR
      "Do not build in-source.
                       Please remove CMakeCache.txt and the CMakeFiles/ directory. Then build out-of-source."
    )
endif()

# CMake modules
include(CMakeDependentOption)

# Compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Threads
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)

# Turn off CGAL Triangulation Assertions and Postconditions
add_definitions(-DCGAL_TRIANGULATION_NO_ASSERTIONS
                -DCGAL_TRIANGULATION_NO_POSTCONDITIONS
                -DCGAL_USE_BASIC_VIEWER
                -DWITH_CGAL_Qt5)

# Disable CLion generation of RelWithDebInfo and MinSizeRel to avoid conflicts
# with CGAL_SetupFlags.cmake
set(CMAKE_CONFIGURATION_TYPES
    "Release"
    "Debug"
    "RelWithDebInfo"
    CACHE STRING ""
    FORCE)

# CGAL
find_package(CGAL COMPONENTS Core Qt5 REQUIRED)
if(CGAL_FOUND)
  # Don't let CGAL override flags
  set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE true)
  set(CGAL_DONT_OVERRIDE_CMAKE_FLAGS TRUE
      CACHE BOOL "Force CGAL to maintain CMAKE flags")
  include(${CGAL_USE_FILE})
  include(CGAL_CreateSingleSourceCGALProgram)
else()
  message(
    FATAL_ERROR
      "Notice: This program requires the CGAL library, and will not be compiled."
    )
endif()

# Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
# Qt Homebrew install location
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.1/lib/cmake/Qt5/")
find_package(Qt5
             COMPONENTS Core
                        Widgets
                        Xml
                        OpenGL
                        REQUIRED)

# Build executable with C++17
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/include)
add_executable(draw_triangulation_3
               ${PROJECT_SOURCE_DIR}/src/draw_triangulation_3.cpp)
target_link_libraries(draw_triangulation_3
                      PRIVATE ${CGAL_LIBRARIES}
                              Qt5::Core
                              Qt5::Widgets
                              Qt5::Xml
                              Qt5::OpenGL)
target_compile_features(draw_triangulation_3 PRIVATE cxx_std_17)

# Tests
enable_testing()

add_test(NAME DrawTriangulations COMMAND $<TARGET_FILE:draw_triangulation_3>)
