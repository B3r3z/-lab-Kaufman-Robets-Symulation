#!/bin/bash
cmake . -B build
cd build 
make
./bin/MiOWSsymulator  # Updated path to the executable
