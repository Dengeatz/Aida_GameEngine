cmake_minimum_required(VERSION 4.0.0 FATAL_ERROR)

set(PROJECT_NAME Aida_GameEngine)
project(Aida_GameEngine)

add_executable(Aida_GameEngine src/main.cpp
	src/Render/ShaderProgram.cpp
	src/Render/ShaderProgram.h
	src/res/ResourcesManager.cpp
	src/res/ResourcesManager.h
)

list(APPEND CMAKE_PREFIX_PATH "src/graphics/glfw/lib/cmake")
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(Aida_GameEngine OpenGL::GL)
target_link_libraries(Aida_GameEngine glfw)

set_target_properties(Aida_GameEngine PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET Aida_GameEngine 
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/src/Resources 
    $<TARGET_FILE_DIR:Aida_GameEngine>/res
)