#!/usr/bin/env bash

set -eu

mkdir -p build

gcc main.c -o build/bin2str-c

g++ -std=c++1z main.cpp -o build/bin2str-cpp

g++ -std=c++1z c++_simplified.cpp -o build/bin2str-cpp-simple

gcc optimized-convert.c -o build/optimized-convert
chmod 755 build/optimized-convert
./build/optimized-convert

export CFLAGS="-I/opt/homebrew/include/ -L/opt/homebrew/lib/"
make
