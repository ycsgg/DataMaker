cmake_minimum_required(VERSION 3.5)

project(CP_DataMaker)

set(
    SOURCES
    src/main.cpp
)
add_compile_options(-std=c++17 -O2)

add_executable(${PROJECT_NAME} ${SOURCES})


target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)