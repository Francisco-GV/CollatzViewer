cmake_minimum_required(VERSION 3.2.0)
project(CollatzViewer VERSION 0.1.0 LANGUAGES CXX)

set(SOURCES src/main.cpp src/testWindow.cpp src/algorithm.cpp)

add_executable(CollatzViewer ${SOURCES})

target_include_directories(CollatzViewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(SFML 2 REQUIRED COMPONENTS system window graphics)

target_link_libraries(CollatzViewer PRIVATE sfml-system sfml-window sfml-graphics)
target_include_directories(CollatzViewer PRIVATE ${SFML_INCLUDE_DIR})

install(TARGETS CollatzViewer)