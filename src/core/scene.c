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

  scene->shader_program = shader_program;

  return scene;
}

void scene_render(GLFWwindow *window, Scene *scene)
{
  glUseProgram(scene->shader_program);
  glUniform1i(glGetUniformLocation(scene->shader_program, "ourTexture"), 0);

  Object *object;
  if (!(object = init_object(0.7, 0.2, 0, 0.25, 0.01, 0.01)))
  {
    scene_free(scene);
    printf("Error: Could not load object\n");
  }
  
  Object *object2;
  if (!(object2 = init_object(0.5, 0.5, 0, 0.25, -0.01, -0.01)))
  {
    scene_free(scene);
    printf("Error: Could not load object\n");
  }

  Object *object3;
  if (!(object3 = init_object(0.2, 0.2, 0, 0.25, 0.01, -0.01)))
  {
    scene_free(scene);
    printf("Error: Could not load object\n");
  }

  Object *object4;
  if (!(object4 = init_object(0.3, 0.7, 0, 0.25, -0.01, 0.01)))
  {
    scene_free(scene);
    printf("Error: Could not load object\n");
  }

  while (!glfwWindowShouldClose(window))
  {
    // inputs
    processInput(window);

    // color
    float time = glfwGetTime() * 2;
    float r, g, b;

    // rendering
    // glClearColor(0.15686274509, 0.16470588235, 0.21176470588, 1.0f);
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object->TEX);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object2->TEX);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object3->TEX);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, object4->TEX);

    glUseProgram(scene->shader_program);
    glBindVertexArray(object->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(object2->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glUseProgram(scene->shader_program);
    glBindVertexArray(object3->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(object4->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    object_bounce(object, time);
    object_bounce(object2, time);
    object_bounce(object3, time);
    object_bounce(object4, time);

    object_update_state(object);
    object_update_state(object2);
    object_update_state(object3);
    object_update_state(object4);

    object_push_state(object);
    object_push_state(object2);
    object_push_state(object3);
    object_push_state(object4);
    
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

  // if (scene->object)
  // {
  //   if (scene->object->VAO)
  //     glDeleteVertexArrays(1, &scene->object->VAO);
  //   if (scene->object->VBO)
  //     glDeleteBuffers(1, &scene->object->VBO);
  //   if (scene->object->EBO)
  //     glDeleteBuffers(1, &scene->object->EBO);
  //   if (scene->object->TEX)
  //    glDeleteTextures(1, &scene->object->TEX);
  //   free(scene->object);
  // }

   free(scene);
}