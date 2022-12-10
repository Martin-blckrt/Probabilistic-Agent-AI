cmake_minimum_required(VERSION 3.23)
project(LostInTheWoods)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
include_directories(.)

add_executable(LostInTheWoods Cell.cpp Cell.h
        Woods.cpp Woods.h ProblemData.h Agent.cpp Agent.h main.cpp Sensor.h Effector.h)
