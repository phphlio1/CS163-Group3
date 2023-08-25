cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

project(CS163_Dictionary)
add_executable(${PROJECT_NAME})

add_subdirectory(src)
add_subdirectory(Dictionary)

target_include_directories(${PROJECT_NAME} PRIVATE
  .
  SFML/include
  Dictionary
  src
  src/frontend)
target_link_directories(${PROJECT_NAME} PRIVATE SFML/lib)
target_link_libraries(${PROJECT_NAME}
  sfml-graphics
  sfml-network
  sfml-window
  sfml-main
  sfml-system)
