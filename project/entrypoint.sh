#!/bin/sh

# Create build directory
mkdir -p build

# Clean up the build directory
rm -rf build/*

# Use GCC to compile the main.cpp and internship.cpp source files with include path to VCPKG installer libraries
g++ -I/opt/vcpkg/installed/x64-linux/include -std=c++17 -O2 -o build/internship src/*.cpp

# Run the application
sh -c "build/internship ${DATA_JSON} ${COUNT}"