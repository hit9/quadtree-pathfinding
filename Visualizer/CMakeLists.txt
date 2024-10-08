cmake_minimum_required(VERSION 3.10)

project(QuadtreePathfindingVisualizer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

find_package(spdlog)
find_package(SDL2_ttf)
find_package(SDL2)
find_package(argparse)

# ----- library imgui ------
file(GLOB IMGUI_SOURCES 3rdParty/imgui/*.cpp)
add_library(imgui ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC "3rdParty/imgui")
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})

# ------ QDPF ---------
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../Source
                 ${CMAKE_CURRENT_BINARY_DIR}/Source)

# ----- QuadtreePathfindingVisualizer ------
file(GLOB VISUALIZER_SOURCES *.cpp)
add_executable(QuadtreePathfindingVisualizer ${VISUALIZER_SOURCES})
target_include_directories(QuadtreePathfindingVisualizer PUBLIC "../Source"
                                                                "3rdParty")

target_link_libraries(
  QuadtreePathfindingVisualizer
  QDPF
  imgui
  spdlog::spdlog
  sdl_ttf::sdl_ttf
  SDL2::SDL2main
  argparse::argparse)
