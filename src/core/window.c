#include "core/window.h"

static void glfw_error_callback(int error, const char* description);
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
static void init_GLFW();

GLFWwindow *init_window()
{
  init_GLFW();

  GLFWwindow *window;
  glfwSetErrorCallback(glfw_error_callback);

  if (!(window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL)))
  {
    glfwTerminate();
    return NULL;
  }

  if (window == NULL)
  {
    printf("Failed to create GLFW window");
    glfwTerminate();
    return NULL;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD");
    return NULL;
  }

  return window;
}

static void glfw_error_callback(int error, const char* description)
{
  fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void init_GLFW() 
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //uncomment this statement to fix compilation on OS X
  #endif
}
