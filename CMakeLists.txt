cmake_minimum_required(VERSION 3.10)

# Set your project name and language
project(Compiler LANGUAGES CXX)

# Specify the C++ standard 
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_compile_options( -g -fdiagnostics-color=always)
file(GLOB SOURCES "src/*.cpp" "src/LexicalAnalysis/*.cpp" "src/Utils/*.cpp")
# Add the executable target (source file(s) location)
add_executable(Compiler ${SOURCES})

# Generate compile_commands.json for IDE tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
