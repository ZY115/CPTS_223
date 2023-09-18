cmake_minimum_required(VERSION 3.16)
project(PA1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)

add_executable(PA1 FileHandler.cpp Game.cpp Game.h FileHandler.h main.cpp player.cpp player.h header.h LinkedList.h)