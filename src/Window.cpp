#include <Aqua/Core/Window.hpp>
#include <Aqua/Core/Assert.hpp>

namespace Aqua {

Window::Window(int width, int height, const char* title) {
	int result = glfwInit();
	ASSERT(result == GLFW_TRUE, "Could not init glfw!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	ASSERT(window != NULL, "Could not create window!");

	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, SizeCallback);
	glfwSetWindowFocusCallback(window, FocusedCallback);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

	glfwMakeContextCurrent(window);

	// Init glad
	result = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ASSERT(result != 0, "Could not load OpenGL!");

	glViewport(0, 0, width, height);
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::ShouldClose() {
	return glfwWindowShouldClose(window);
}

void Window::PollEvents() {
	glfwPollEvents();
}

void Window::SwapBuffers() {
	glfwSwapBuffers(window);
}

GLFWwindow* Window::GetWindow() {
	return window;
}

vec2 Window::Size() {
	return vec2((float)this->width, (float)this->height);
}

vec2 Window::FramebufferSize() {
	return vec2((float)this->fbwidth, (float)this->fbheight);
}

void Window::SizeCallback(GLFWwindow* window, int in_width, int in_height) {
	Window* w = (Window*)glfwGetWindowUserPointer(window);
	ASSERT(w != NULL, "Could not get window usr ptr!!");
	w->HandleResize(in_width, in_height);	
}

void Window::HandleResize(int width, int height) {
	this->width = width;
	this->height = height;
	glViewport(0, 0, width, height);
}

void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height){
	Window* w = (Window*)glfwGetWindowUserPointer(window);
	ASSERT(w != NULL, "Could not get window usr ptr!!");
	w->HandleFramebufferResize(width, height);
}

void Window::HandleFramebufferResize(int width, int height) {
	this->fbwidth = width;
	this->fbheight = height;
	glViewport(0, 0, fbwidth, fbheight);
}

void Window::FocusedCallback(GLFWwindow* window, int focused) {
	Window* w = (Window*)glfwGetWindowUserPointer(window);
	ASSERT(w != NULL, "Could not get window usr ptr!!");
	w->HandleFocusChanged(focused);
}

void Window::HandleFocusChanged(int focused) {
	if (focused) {
		focusedState = FocusedState::FOCUSED;
	} else {
		focusedState = FocusedState::UNFOCUSED;
	}
}
}
