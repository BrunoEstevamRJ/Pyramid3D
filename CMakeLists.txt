cmake_minimum_required(VERSION 3.10)
project(Pyramid)

set(CMAKE_CXX_STANDARD 17)

# Diretório dos headers (GLAD, GLM)
include_directories(include)

# GLAD está em src/gl.c
add_library(glad STATIC src/gl.c)

# Encontra GLFW via pkg-config (Linux)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

# Executável principal
add_executable(Pyramid src/main.cpp)

# Inclui headers do GLFW e da pasta local
target_include_directories(Pyramid PRIVATE
    ${GLFW_INCLUDE_DIRS}
    include
)

# Linka GLAD, GLFW e outras libs
target_link_libraries(Pyramid
    glad
    ${GLFW_LIBRARIES}
    m
    dl
)

# No Windows, linka OpenGL manualmente
if (WIN32)
    target_link_libraries(Pyramid opengl32)
endif()
