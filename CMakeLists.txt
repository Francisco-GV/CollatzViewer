cmake_minimum_required(VERSION 3.2.0)
project(CollatzViewer VERSION 0.1.0 LANGUAGES CXX)

add_executable(CollatzViewer src/main.cpp)

find_package(SFML 2 REQUIRED COMPONENTS graphics)

target_link_libraries(CollatzViewer PRIVATE sfml-graphics)
target_include_directories(CollatzViewer PRIVATE ${SFML_INCLUDE_DIR})

install(TARGETS CollatzViewer)