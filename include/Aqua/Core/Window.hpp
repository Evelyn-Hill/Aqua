#include <Aqua/Core/Types.hpp>
#include <Aqua/Core/Log.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Aqua {
class Window {
public:
  // Creates a new window.
  Window(int width, int height, const char *title);
  Window(const Window &other) = delete;
  Window operator=(const Window &other) = delete;

  ~Window();

  // Returns true if the window should close.
  bool ShouldClose();

  void PollEvents();
  void SwapBuffers();
  
  GLFWwindow* GetWindow();  

  vec2 Size();

  vec2 FramebufferSize();

  enum FocusedState : uint8_t {
    FOCUSED,
    UNFOCUSED,
  };

private:
  GLFWwindow *window;

  int width;
  int height;

  int fbwidth;
  int fbheight;

  FocusedState focusedState;

  static void SizeCallback(GLFWwindow* window, int in_width, int in_height);
  void HandleResize(int width, int height);

  static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
  void HandleFramebufferResize(int width, int height);
  
  static void FocusedCallback(GLFWwindow* window, int focused);
  void HandleFocusChanged(int focused);
};
}
