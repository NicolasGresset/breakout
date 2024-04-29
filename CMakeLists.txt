cmake_minimum_required(VERSION 3.0)
project(Breakout)

include_directories(include)


# Dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

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

# Check if GAME_TESTING is passed as an argument
if(GAME_TESTING)
  message("GAME_TESTING is defined")
  # Add compile definition if GAME_TESTING is passed
  target_compile_definitions(main PRIVATE GAME_TESTING)
endif()


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Lier les bibliothèques SDL2
target_link_libraries(main ${SDL2_LIBRARIES} SDL2)

set(SDL2_TTF_INCLUDE_DIR "/usr/include/SDL2" CACHE STRING "SDL2_ttf include directory")
set(SDL2_TTF_LIBRARY "/usr/lib/x86_64-linux-gnu/libSDL2_ttf.so" CACHE STRING "SDL2_ttf library")
include_directories(${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(main ${SDL2_TTF_LIBRARY})
