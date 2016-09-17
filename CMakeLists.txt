cmake_minimum_required (VERSION 2.6)
project (OpenMP)
# Section for injecting a version number into a hpp file.
set (OpenMP_VERSION_MAJOR 1)
set (OpenMP_VERSION_MINOR 0)

# Configure a header file to inject the version information
configure_file (
        "${PROJECT_SOURCE_DIR}/openmp_speed.hpp.in"
        "${PROJECT_BINARY_DIR}/openmp_speed.hpp"
        )

# Add the binary tree to the search path for include files
# so that we will find openmp_speed.h when configured.
include_directories ("${PROJECT_BINARY_DIR}")

#Find Armadillo
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

#Find OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
#Set up the flags for compile.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -Wunreachable-code -O0 -DDEBUG -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -DNDEBUG -O2")
#I am going to use come C++11 stuff.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Allow library to be optionally compiled.
option (USE_OPEN_MP_FUNCTIONS "Use open mp functions" ON)

if (USE_OPEN_MP_FUNCTIONS)
    # Include the subfolder with the OpenMP functions.
    include_directories ("${PROJECT_SOURCE_DIR}/open_mp_functions")
    add_subdirectory (open_mp_functions)
    set (EXTRA_LIBS ${EXTRA_LIBS} open_mp_functions)
endif (USE_OPEN_MP_FUNCTIONS)

# Add the executable
add_executable(OpenMP openmp_speed.cpp)
target_link_libraries (OpenMP ${EXTRA_LIBS})
target_link_libraries(OpenMP ${ARMADILLO_LIBRARIES})


