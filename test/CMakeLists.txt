file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")
add_library(${PROJECT_NAME}_lib ${SOURCES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(GTest CONFIG REQUIRED)
file(GLOB_RECURSE TEST_SOURCES "*.cpp")
add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)