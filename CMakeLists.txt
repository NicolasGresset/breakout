cmake_minimum_required(VERSION 3.0)
project(Breakout)

include_directories(include)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Liste de tous les fichiers sources
file(GLOB SOURCES "src/*.cpp")



set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Déplacez les fichiers de build dans le dossier build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Spécifiez l'exécutable que vous souhaitez créer
add_executable(main ${SOURCES})

# Lier les bibliothèques SDL2
target_link_libraries(main ${SDL2_LIBRARIES})