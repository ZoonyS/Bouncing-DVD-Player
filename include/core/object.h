#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>

#define OBJECT_VERT_POSITION_X 0
#define OBJECT_VERT_POSITION_Y 1
#define OBJECT_VERT_POSITION_Z 2

#define OBJECT_VERT_COLOR_R 3
#define OBJECT_VERT_COLOR_G 4
#define OBJECT_VERT_COLOR_B 5

#define OBJECT_VERT_TEXTURE_U 6
#define OBJECT_VERT_TEXTURE_V 7

#define OBJECT_TOP_RIGHT_VERTEX 0
#define OBJECT_BOTTOM_RIGHT_VERTEX 8
#define OBJECT_BOTTOM_LEFT_VERTEX 16
#define OBJECT_TOP_LEFT_VERTEX 24

typedef struct {
  int id;
  float posx;
  float posy;
  float posz;
  float scale;
  float r;
  float g;
  float b;
  float velocityx;
  float velocityy;
  float *texture_coords;
  float vertices[32];
  unsigned int *indices;
  GLuint VAO;
  GLuint VBO;
  GLuint EBO;
  GLuint TEX;
} Object;

Object* init_object(float position_x, float position_y, float position_z, float scale, float velocity_x, float velocity_y);

void object_bounce(Object *object, float time);

void object_update_state(Object *object);

void object_push_state(Object *object);

void link_vertex_attributes();

#endif // !OBJECT_H
