cmake_minimum_required(VERSION 3.10)
project(Pyramid)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(glad STATIC src/gl.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(Pyramid src/main.cpp)  

target_include_directories(Pyramid PRIVATE
    ${GLFW_INCLUDE_DIRS}
    include
)

target_link_libraries(Pyramid
    glad
    ${GLFW_LIBRARIES}
    m
    dl
)

if (WIN32)
    target_link_libraries(Pyramid opengl32)
endif()

add_custom_command(TARGET Pyramid POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_SOURCE_DIR}/wall.jpg
    $<TARGET_FILE_DIR:Pyramid>
)
