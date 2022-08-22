#!/bin/bash

g++ -std=c++17 -O2 -Wall -Wextra -fsanitize=address -g $1.cpp -o $1
./$1 < $1.in > out.txt
cat out.txt
