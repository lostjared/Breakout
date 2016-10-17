# Breakout
This is a work in progress going to be a
Simple 2D Game written in C++ using SDL2 
Just practice project for fun

This application requires SDL2, SDL2_ttf, SDL_image (v1.2).
To make it easy just compile and install to /usr/local
then to compile this project first run:

$ ./autogen.sh

then

$ mkdir build && cd build

$ ../configure

$ make

to run the program from build directory use

$ src/Breakout ../data 1280 720

or whereever the program is path the data directory as first argument
followed by the desired resolution of the program

