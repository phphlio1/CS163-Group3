cmake_minimum_required(VERSION 3.21)
project(Dictionary LANGUAGES CXX)

add_executable(Dictionary src/main.cpp)

add_subdirectory(src)
add_subdirectory(UI/SFML/src/SFML/Graphics)
add_subdirectory(UI/SFML/include/SFML/Graphics)

target_include_directories(${PROJECT_NAME}
    PUBLIC UI/SFML/src/SFML/Graphics
    PUBLIC UI/SFML/include/SFML/Graphics
    PUBLIC src)

link_directories(${PROJECT_NAME}
    PRIVATE UI/SFML/src/SFML/Graphics
    PRIVATE UI/SFML/include/SFML/Graphics
    PRIVATE src)
target_link_libraries(${PROJECT_NAME} 
    PRIVATE sfml-graphics
    sources)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

install(TARGETS Dictionary)