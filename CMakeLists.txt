cmake_minimum_required(VERSION 3.2.0)
project(CollatzViewer VERSION 0.1.0 LANGUAGES CXX)

set(SOURCES src/main.cpp src/test.cpp src/graph.cpp src/algorithm.cpp)

add_executable(CollatzViewer ${SOURCES})

target_include_directories(CollatzViewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SFML 2 REQUIRED COMPONENTS graphics)

target_link_libraries(CollatzViewer PRIVATE sfml-graphics)
target_include_directories(CollatzViewer PRIVATE ${SFML_INCLUDE_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})