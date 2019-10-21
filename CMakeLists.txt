cmake_minimum_required(VERSION 3.15)
project(qtpass)
set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(VERSION="1.3.2")

find_package(Qt5LinguistTools)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Svg REQUIRED)

add_subdirectory(src)
add_subdirectory(main)