cmake_minimum_required(VERSION 3.5)

project(YapoLand LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(YapoLand YapoLand.cpp YapoLandSocket.hpp)
target_link_libraries(${PROJECT_NAME} -lsfml-graphics -lsfml-window)