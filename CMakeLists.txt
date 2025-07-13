cmake_minimum_required(VERSION 4.0)
project(Asteroids CXX)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Collect all source files from src directory
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.c"
)

# Collect all header files from include directory (optional, for IDE organization)
file(GLOB_RECURSE HEADERS 
    "include/*.h"
    "include/*.hpp"
) 

# Create executable with all source files
add_executable(Asteroids ${SOURCES} ${HEADERS})

# Add include directory so your source files can find headers
target_include_directories(Asteroids PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Set C++ standard
target_compile_features(Asteroids PRIVATE cxx_std_23)

# Link SFML libraries
target_link_libraries(Asteroids PRIVATE SFML::Graphics)
