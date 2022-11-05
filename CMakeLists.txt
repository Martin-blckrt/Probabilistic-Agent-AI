cmake_minimum_required(VERSION 3.23)
project(LostInTheWoods)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LostInTheWoods
        Woods.cpp
        Woods.h ProblemData.h Agent.cpp Agent.h bayes.h main.cpp Cell.cpp Cell.h)
