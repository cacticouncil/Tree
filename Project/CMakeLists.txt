cmake_minimum_required(VERSION 3.5)
project(TreeAlgorithmTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
set(CMAKE_EXE_LINKER_FLAGS "-static")
set(SOURCE_FILES TreeMain.cpp nvwa/debug_new.cpp)
add_executable(TreeAlgorithmTest ${SOURCE_FILES})