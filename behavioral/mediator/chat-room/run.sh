#!/usr/bin/bash

echo "Compiling..."
g++ -c main.cpp Person.cpp ChatRoom.cpp

echo "Linking together..."
g++ main.o Person.o ChatRoom.o -o a.out

echo -e "Running...\n"
./a.out
