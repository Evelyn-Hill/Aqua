cmake_minimum_required(VERSION 4.0)

project(Aqua)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/glad)
#add_subdirectory(vendor/freetype)

set(SRCS
	src/Log.cpp
	src/Window.cpp
	src/Game.cpp
	src/Shader.cpp
	src/AssetManager.cpp
	src/Texture.cpp
	src/Renderer.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRCS})

target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm glad)

target_include_directories(${PROJECT_NAME} PUBLIC 
	include/
	vendor/stb
)
