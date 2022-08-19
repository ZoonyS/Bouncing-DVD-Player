#ifndef SCENE_H
#define SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "core/shader_loader.h"
#include "core/object.h"
#include "core/input.h"

#define MAX_OBJECTS 10

typedef struct {
  GLuint shader_program;
  //View *view;
  Object object[MAX_OBJECTS];   
} Scene;

Scene* init_scene();
void scene_render(GLFWwindow *window, Scene *scene);

void scene_add_object(Scene *scene);

void scene_free();

#endif // !SCENE_H
