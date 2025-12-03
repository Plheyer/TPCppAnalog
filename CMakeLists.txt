cmake_minimum_required(VERSION 4.0)
project(TpCppAnalog)

set(CMAKE_CXX_STANDARD 20)

add_executable(TpCppAnalog main.cpp
        LogEntry.h
        LogEntry.cpp
        Graph.cpp
        ApacheLogStream.cpp)
