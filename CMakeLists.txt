cmake_minimum_required(VERSION 3.14)

# Setting default variables.

set(PROJECT_NAME Wolf3D)
set(CMAKE_CXX_STANDARD 17)
set(PROJECT_SRCS
        src/main.cpp
        src/Display.cpp
        src/Level.cpp
        src/Game.cpp
        src/Player.cpp
        src/Position.cpp
        src/Engine.cpp
        src/Minimap.cpp
        src/ARay.cpp
        src/VerticalRay.cpp
        src/HorizontalRay.cpp)

# Defining the project.

project(${PROJECT_NAME})

# Adding the executable.

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

# Adding the math definition (M_PI, ...)

add_definitions(-D_USE_MATH_DEFINES)

# Including the project headers.

include_directories(include)

# Resolving SFML dependency.

find_package(SFML COMPONENTS audio graphics network system window REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-network sfml-system sfml-window)
endif ()
