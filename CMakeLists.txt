cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)


project(Aida_GameEngine)

add_executable(Aida_GameEngine src/main.cpp)

list(APPEND CMAKE_PREFIX_PATH "src/graphics/glfw/lib/cmake")
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(Aida_GameEngine OpenGL::GL)
target_link_libraries(Aida_GameEngine glfw)