cmake_minimum_required(VERSION 3.20)

project(chip-8-emulator LANGUAGES C CXX ASM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_TESTING "Enable testing" ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${ALL_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL GLUT::GLUT)

if(ENABLE_TESTING)
    add_subdirectory(test)
endif()