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
include(CheckCXXCompilerFlag)

# CMake functions

# Check if compiler flag supported
function(enable_cxx_compiler_flag_if_supported flag)
  string(FIND "${CMAKE_CXX_FLAGS}" "${flag}" flag_already_set)
  if(flag_already_set EQUAL -1)
    check_cxx_compiler_flag("${flag}" flag_supported)
    if(flag_supported)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${flag}" PARENT_SCOPE)
    endif()
    unset(flag_supported CACHE)
  endif()
endfunction()

# Compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compiler flags
enable_cxx_compiler_flag_if_supported("-Wmisleading-indentation")
enable_cxx_compiler_flag_if_supported("-frounding-math")
enable_cxx_compiler_flag_if_supported("-Wduplicated-cond")
enable_cxx_compiler_flag_if_supported("-Wuplicated-branches")
enable_cxx_compiler_flag_if_supported("-Wlogical-op")
enable_cxx_compiler_flag_if_supported("-Wuseless-cast")
enable_cxx_compiler_flag_if_supported("-Wall")
enable_cxx_compiler_flag_if_supported("-Wno-comment")
enable_cxx_compiler_flag_if_supported("-Wextra")
enable_cxx_compiler_flag_if_supported("-Wshadow")
enable_cxx_compiler_flag_if_supported("-Wnon-virtual-dtor")
enable_cxx_compiler_flag_if_supported("-Wold-style-cast")
enable_cxx_compiler_flag_if_supported("-Wcast-align")
enable_cxx_compiler_flag_if_supported("-Wunused")
enable_cxx_compiler_flag_if_supported("-Woverloaded-virtual")
enable_cxx_compiler_flag_if_supported("-Wpedantic")
enable_cxx_compiler_flag_if_supported("-Wconversion")
enable_cxx_compiler_flag_if_supported("-Wsign-conversion")
enable_cxx_compiler_flag_if_supported("-Wnull-dereference")
enable_cxx_compiler_flag_if_supported("-Wdouble-promotion")
enable_cxx_compiler_flag_if_supported("-Wformat=2")
enable_cxx_compiler_flag_if_supported("-Werror=return-type")

# Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/5.12.1/lib/cmake/Qt5/")
find_package(Qt5 COMPONENTS Core Widgets Xml OpenGL REQUIRED)

# Build executable with C++17
include_directories(BEFORE ${PROJECT_SOURCE_DIR}/include)
add_executable(draw_triangulation_3 ${PROJECT_SOURCE_DIR}/src/draw_triangulation_3.cpp)
target_link_libraries(draw_triangulation_3 PRIVATE ${CGAL_LIBRARIES} Qt5::Core Qt5::Widgets Qt5::Xml Qt5::OpenGL)
target_compile_features(draw_triangulation_3 PRIVATE cxx_std_17)

# Tests
enable_testing()

add_test(NAME DrawTriangulations COMMAND $<TARGET_FILE:draw_triangulation_3>)