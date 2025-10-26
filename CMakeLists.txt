cmake_minimum_required(VERSION 3.28)

project(saved_games_backup VERSION 0.1 LANGUAGES CXX)

add_library(filebackup STATIC src/filebackup.cpp)
target_include_directories(filebackup PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
set_target_properties(filebackup PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_executable(backup_agent src/main.cpp)
target_include_directories(backup_agent PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(backup_agent 
    PRIVATE
        FileBackup
)  
set_target_properties(backup_agent PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)