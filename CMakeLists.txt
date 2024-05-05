cmake_minimum_required(VERSION 3.20)
project(LovelyClicker)

# Set C++ standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(LovelyClicker Sources/Main.c Sources/State.c)

target_include_directories(LovelyClicker PRIVATE Include)
target_link_libraries(LovelyClicker PRIVATE User32)
