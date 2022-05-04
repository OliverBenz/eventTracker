# ----- Get QT6 -----
find_package(Qt6 REQUIRED COMPONENTS Gui Widgets Sql)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# ----- Setup project ------
set(targetName "demTracker" CACHE STRING "Name of the main executable.")

# Get files to build
file(GLOB_RECURSE sourceFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE headerFiles ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

# Create library
add_executable(${targetName}
    ${sourceFiles}
    ${headerFiles}
)

# Linking
target_link_libraries(${targetName} PRIVATE Qt6::Gui Qt6::Widgets Qt6::Sql)

# Setup project settings
set_project_warnings(${targetName})      # Which warnings to enable
set_compile_options(${targetName})       # Which extra compiler flags to enable
set_output_directory(${targetName})      # Set the output directory of the library

# Specify version
target_compile_definitions(${targetName} PUBLIC VERSION_MAJOR=0)
target_compile_definitions(${targetName} PUBLIC VERSION_MINOR=1)
target_compile_definitions(${targetName} PUBLIC VERSION_PATCH=0)