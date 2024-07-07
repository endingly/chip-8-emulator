cmake_minimum_required(VERSION 3.15)


project(chip-8-emulator LANGUAGES C CXX ASM)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES "src/*.cpp")
list(REMOVE_ITEM SOURCES "src/main.cpp")
add_library(${PROJECT_NAME}_lib ${SOURCES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC include)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
add_executable(${PROJECT_NAME}_bin src/main.cpp)
target_link_libraries(
    ${PROJECT_NAME}_bin 
    ${PROJECT_NAME}_lib 
    OpenGL::GL 
    GLUT::GLUT
)

find_package(GTest CONFIG REQUIRED)
file(GLOB_RECURSE TEST_SOURCES "test/*.cpp")
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)