cmake_minimum_required(VERSION 3.10)

# Set your project name and language
project(Compiler LANGUAGES CXX)

# Specify the C++ standard 
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_BUILD_TYPE Debug) # Enables debugging symbols (-g flag)
add_compile_options( -g -fdiagnostics-color=always)
file(GLOB SOURCES "src/*.cpp" "src/LexicalAnalysis/*.cpp" "src/Utils/*.cpp" "src/SyntaxAnalysis/*.cpp" "src/CodeGeneration/*.cpp")
# Add the executable target (source file(s) location)
add_executable(Compiler ${SOURCES})

# Generate compile_commands.json for IDE tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
