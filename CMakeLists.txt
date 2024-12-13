cmake_minimum_required(VERSION 3.10)

project(pong)
find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_ttf SDL2_mixer)
