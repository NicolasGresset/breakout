cmake_minimum_required(VERSION 3.0)
project(Breakout)

include_directories(include)


# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})


file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")
# add_subdirectory(src)
# add_subdirectory(include)
# add_subdirectory(gui)
# add_subdirectory(object)
# add_subdirectory(utils)



set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Déplacez les fichiers de build dans le dossier build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Spécifiez l'exécutable que vous souhaitez créer
add_executable(main ${SOURCES})

# Définir les options de compilation pour votre projet
target_compile_options(main PRIVATE -Wall -Wextra --std=c++17)

# Lier les bibliothèques SDL2
target_link_libraries(main ${SDL2_LIBRARIES} SDL2_ttf)