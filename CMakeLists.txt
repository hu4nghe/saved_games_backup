cmake_minimum_required(VERSION 3.28)
project(saved_games_backup VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(filebackup STATIC src/filebackup.cpp)
target_include_directories(filebackup PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_executable(backup_agent src/main.cpp)
target_link_libraries(backup_agent PRIVATE filebackup)