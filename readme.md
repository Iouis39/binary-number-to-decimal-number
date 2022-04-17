# Binary to Decimal conversion (a training module for starters)

The general task was:

* read a series of 0 and 1 from the console
* print its decimal representation
* repeast until `empty` string is given

## build

This project uses `build.sh` to build all binaries into ./build/.

## main.c

C implemenation

* uses a safe way to read from console
* the signature of `int convertBinaryToDecimal(int input[], int numberOfInputElements, int* result)` had to used

## main.cpp

This shows a possible transformation from main.c into a C++ implemenation. The basic idea of `convertBinaryToDecimal` was kept.

## c++_simplified.cpp

This implements the general idea in C++ as simple as possible.

## optimized-convert.c

This just shows how a string can be converted to decimal.
