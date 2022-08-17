#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <glad/glad.h>

GLuint loadShaderProgramFromFile(GLchar* vertexPath, GLchar* fragmentPath);

#endif
