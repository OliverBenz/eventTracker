cmake_minimum_required(VERSION 3.12)

project("Dementsprechend")
set(CMAKE_CXX_STANDARD 17)

# Setup project settings
include(cmake/ProjectSettings.cmake)
include(cmake/CompilerWarnings.cmake)

add_subdirectory(src)