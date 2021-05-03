# Note: FetchContent_MakeAvailable was added in CMake 3.14
cmake_minimum_required(VERSION 3.14)

project(vips-microbench
        VERSION 1.0.0
        DESCRIPTION "libvips micro-benchmarks"
        LANGUAGES
            CXX
        )

# Set output directories in which to build the target files
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Set a default build type if none was specified
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Let's enable C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler flags
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG") # Optimize for performance
    set(CMAKE_EXE_LINKER_FLAGS "-s")   # Strip binary
endif()

include(FetchContent)

# Find libvips (required)
find_package(PkgConfig)
pkg_check_modules(VIPS vips-cpp>=8.11 REQUIRED)

# Add google/benchmark dependency
add_subdirectory(third_party/benchmark)

add_subdirectory(src)
