cmake_minimum_required(VERSION 3.13)

project(Dictionary)
add_executable(${PROJECT_NAME})

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} PRIVATE
  SFML/include
  src
  src/frontend)
target_link_directories(${PROJECT_NAME} PRIVATE SFML/lib)
target_link_libraries(${PROJECT_NAME}
  sfml-graphics
  sfml-network
  sfml-window
  sfml-main
  sfml-system)
