cmake_minimum_required(VERSION 4.0)

project(Aqua)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/glad)

set(SRCS
	src/Window.cpp
	src/Game.cpp
	src/Log.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRCS})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm glad)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
