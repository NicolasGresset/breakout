cmake_minimum_required(VERSION 3.0)
project(Breakout)

include_directories(include)

# Liste de tous les fichiers sources
file(GLOB SOURCES "src/*.cpp")

# Spécifiez l'exécutable que vous souhaitez créer
add_executable(main ${SOURCES})

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Déplacez les fichiers de build dans le dossier build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
