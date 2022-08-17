#ifndef WINDOW_H
#define WINDOW_H

#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/config.h"

GLFWwindow* init_window();
void window_swap_buffer(struct GLFWwindow* window);
void window_poll_event();
void window_close();

#endif // !WINDOW_H
