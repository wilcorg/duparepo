cmake_minimum_required(VERSION 3.30)
project(bimap)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

add_executable(bimap main.cpp
        include/bimap/ConstBiMapIterator.hpp)

target_link_libraries(${PROJECT_NAME} src-bimap)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${INCLUDE_DIR}
)
