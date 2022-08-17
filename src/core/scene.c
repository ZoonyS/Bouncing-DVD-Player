#include "core/scene.h"

Scene *init_scene()
{
  Scene *scene = (Scene *) malloc(sizeof(Scene));
  if (!scene)
  {
    printf("Error: Could not allocate memory for scene.\n");
    return NULL;
  }
  memset(scene, 0, sizeof(Scene));

  GLuint shader_program = loadShaderProgramFromFile((GLchar *) "res/shaders/simple.vs.glsl", (GLchar *) "res/shaders/simple.fs.glsl");
  if (shader_program == 0)
  {
    scene_free(scene);
    printf("Error: Could not load shader program.\n");
    return NULL;
  }

  Object *object;
  if (!(object = init_object(0.70, 0.1, 0, 0.25)))
  {
    scene_free(scene);
    printf("Error: Could not load object\n");
    return NULL;
  }

  scene->shader_program = shader_program;
  scene->object = object;

  return scene;
}

void scene_render(GLFWwindow *window, Scene *scene)
{
  glUseProgram(scene->shader_program);
  glUniform1i(glGetUniformLocation(scene->shader_program, "ourTexture"), 0);

  float xvelocity = -0.005;
  float yvelocity = -0.005;

  int randomnumber;

  while (!glfwWindowShouldClose(window))
  {
    // inputs
    processInput(window);

    // color
    float time = glfwGetTime() * 2;
    float r, g, b;

    // rendering
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->object->TEX);

    glUseProgram(scene->shader_program);
    glBindVertexArray(scene->object->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    scene->object->posx -= xvelocity;
    scene->object->posy -= yvelocity;

    if (scene->object->posx <= -1 || scene->object->posx + scene->object->scale >= 1)
    {
      getRgbRainbow(&r, &g, &b, time);

      xvelocity = -xvelocity;
      scene->object->r = r;
      scene->object->g = g;
      scene->object->b = b;
    }
    if (scene->object->posy <= -1 || scene->object->posy + scene->object->scale >= 1)
    {
      getRgbRainbow(&r, &g, &b, time);

      yvelocity = -yvelocity;
      scene->object->r = r;
      scene->object->g = g;
      scene->object->b = b;
    }

    object_update_state(scene->object);
    object_push_state(scene->object);
    
    // swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

 glfwTerminate();
}

void scene_free(Scene *scene)
{
  if (scene == NULL)
    return;

  if (scene->shader_program)
    glDeleteProgram(scene->shader_program);

  //if (scene->view)
  //  free(scene->view);

  if (scene->object)
  {
    if (scene->object->VAO)
      glDeleteVertexArrays(1, &scene->object->VAO);
    if (scene->object->VBO)
      glDeleteBuffers(1, &scene->object->VBO);
    if (scene->object->EBO)
      glDeleteBuffers(1, &scene->object->EBO);
    if (scene->object->TEX)
     glDeleteTextures(1, &scene->object->TEX);
    free(scene->object);
  }

   free(scene);
}

void getRgbRainbow(float *r, float *g, float *b, float time)
{
  *r = sin(time) * 0.5 + 0.5;
  *g = sin(time * 0.5) * 0.5 + 0.5;
  *b = sin(time * 0.25) * 0.5 + 0.5;
}