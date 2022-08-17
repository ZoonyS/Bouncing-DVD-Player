#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/window.h"
#include "core/scene.h"

int main(int argc, char *argv[])
{
  GLFWwindow *window = init_window();
  Scene *scene = init_scene();

  scene_render(window, scene);

  return 0;
}
