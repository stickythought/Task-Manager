cmake_minimum_required(VERSION 3.10)
project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(task_manager ${SOURCES})
