#include "core/object.h"

Object *init_object(float position_x, float position_y, float position_z, float scale)
{
  Object *object = (Object *) malloc(sizeof(Object));
  if (!object)
  {
    printf("Error: Could not allocate memory for object.\n");
    return NULL;
  }

  object->scale = scale;
  object->posx = position_x;
  object->posy = position_y;
  object->posz = position_z;

  // vertex data
  object_update_state(object);

  unsigned int indices[] = {
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
  };
  object->indices = indices;
  
  // vertex buffer object
  // provides methods for uploading vertex data to GPU, e.g (pos, normal vec, color, ... )
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO); // copy our vertices array in a buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(object->vertices), object->vertices, GL_STATIC_DRAW);
  object->VBO = VBO;

  // vertex array object
  // stores all the state needed to supply vertex data, e.g. format of vertex data and buffer object
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);  
  glBindVertexArray(VAO);
  object->VAO = VAO;

  // elemental buffer object
  // stores indices that opengl uses to decide what vertices to draw
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); // render the triangles from index buffer
  object->EBO = EBO;

  // link attributes
  link_vertex_attributes();

  // texture
  unsigned int TEX;
  glGenTextures(1, &TEX);
  glBindTexture(GL_TEXTURE_2D, TEX); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

  // wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);      
  // filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
  object->TEX = TEX;

  // load image, create texture, generate mipmaps
  int width, height, nr_channels;
  stbi_set_flip_vertically_on_load(1); // flip loaded textures on y axis

  unsigned char *data = stbi_load("res/images/DVD.png", &width, &height, &nr_channels, 4);
  if (data)
  {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
    printf("error loading texture\n");
  }
  stbi_image_free(data);

  return object;
}

void object_update_state(Object *object)
{
  // top right
  // position
  object->vertices[OBJECT_TOP_RIGHT_VERTEX + OBJECT_VERT_POSITION_X] = object->posx + object->scale; // for position we're drawing from bottom left
  object->vertices[OBJECT_TOP_RIGHT_VERTEX + OBJECT_VERT_POSITION_Y] = object->posy + object->scale;
  object->vertices[OBJECT_TOP_RIGHT_VERTEX + OBJECT_VERT_POSITION_Z] = object->posz;
  // color
  object->vertices[OBJECT_TOP_RIGHT_VERTEX + OBJECT_VERT_COLOR_R] = object->r;
  object->vertices[OBJECT_TOP_RIGHT_VERTEX + OBJECT_VERT_COLOR_G] = object->g;
  object->vertices[OBJECT_TOP_RIGHT_VERTEX + OBJECT_VERT_COLOR_B] = object->b;
  // texture uv
  object->vertices[OBJECT_TOP_RIGHT_VERTEX + OBJECT_VERT_TEXTURE_U] = 1.0f;
  object->vertices[OBJECT_TOP_RIGHT_VERTEX + OBJECT_VERT_TEXTURE_V] = 1.0f;
  // bottom right
  // position
  object->vertices[OBJECT_BOTTOM_RIGHT_VERTEX + OBJECT_VERT_POSITION_X] = object->posx + object->scale;
  object->vertices[OBJECT_BOTTOM_RIGHT_VERTEX + OBJECT_VERT_POSITION_Y] = object->posy;
  object->vertices[OBJECT_BOTTOM_RIGHT_VERTEX + OBJECT_VERT_POSITION_Z] = object->posz;
  // color
  object->vertices[OBJECT_BOTTOM_RIGHT_VERTEX + OBJECT_VERT_COLOR_R] = object->r;
  object->vertices[OBJECT_BOTTOM_RIGHT_VERTEX + OBJECT_VERT_COLOR_G] = object->g;
  object->vertices[OBJECT_BOTTOM_RIGHT_VERTEX + OBJECT_VERT_COLOR_B] = object->b;
  // texture uv
  object->vertices[OBJECT_BOTTOM_RIGHT_VERTEX + OBJECT_VERT_TEXTURE_U] = 1.0f;
  object->vertices[OBJECT_BOTTOM_RIGHT_VERTEX + OBJECT_VERT_TEXTURE_V] = 0.0f;
  // bottom left
  // position
  object->vertices[OBJECT_BOTTOM_LEFT_VERTEX + OBJECT_VERT_POSITION_X] = object->posx;
  object->vertices[OBJECT_BOTTOM_LEFT_VERTEX + OBJECT_VERT_POSITION_Y] = object->posy;
  object->vertices[OBJECT_BOTTOM_LEFT_VERTEX + OBJECT_VERT_POSITION_Z] = object->posz;
  // color
  object->vertices[OBJECT_BOTTOM_LEFT_VERTEX + OBJECT_VERT_COLOR_R] = object->r;
  object->vertices[OBJECT_BOTTOM_LEFT_VERTEX + OBJECT_VERT_COLOR_G] = object->g;
  object->vertices[OBJECT_BOTTOM_LEFT_VERTEX + OBJECT_VERT_COLOR_B] = object->b;
  // texture uv
  object->vertices[OBJECT_BOTTOM_LEFT_VERTEX + OBJECT_VERT_TEXTURE_U] = 0.0f;
  object->vertices[OBJECT_BOTTOM_LEFT_VERTEX + OBJECT_VERT_TEXTURE_V] = 0.0f;
  // top left
  // position
  object->vertices[OBJECT_TOP_LEFT_VERTEX + OBJECT_VERT_POSITION_X] = object->posx;
  object->vertices[OBJECT_TOP_LEFT_VERTEX + OBJECT_VERT_POSITION_Y] = object->posy + object->scale;
  object->vertices[OBJECT_TOP_LEFT_VERTEX + OBJECT_VERT_POSITION_Z] = object->posz;
  // color
  object->vertices[OBJECT_TOP_LEFT_VERTEX + OBJECT_VERT_COLOR_R] = object->r;
  object->vertices[OBJECT_TOP_LEFT_VERTEX + OBJECT_VERT_COLOR_G] = object->g;
  object->vertices[OBJECT_TOP_LEFT_VERTEX + OBJECT_VERT_COLOR_B] = object->b;
  // texture uv
  object->vertices[OBJECT_TOP_LEFT_VERTEX + OBJECT_VERT_TEXTURE_U] = 0.0f;
  object->vertices[OBJECT_TOP_LEFT_VERTEX + OBJECT_VERT_TEXTURE_V] = 1.0f;
}

void object_push_state(Object *object)
{
  // update VBO
  glBindBuffer(GL_ARRAY_BUFFER, object->VBO); // copy our vertices array into buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(object->vertices), object->vertices, GL_STATIC_DRAW);
}

// void object_move(Object *object, float nposx, float nposy)
// {
//   object->posx = nposx;
//   object->posy = nposy;

//   // vertex data
//   float vertices[] = {
//     // positions                                                      // colors           // texture coords
//     object->posx+object->scale,  object->posy+object->scale, 0.0f,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f, // top right
//     object->posx+object->scale, object->posy, 0.0f,                   1.0f, 1.0f, 1.0f,   1.0f, 0.0f, // bottom right
//     object->posx, object->posy, 0.0f,                                 1.0f, 1.0f, 1.0f,   0.0f, 0.0f, // bottom left
//     object->posx,  object->posy+object->scale, 0.0f,                  1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
//   };

//   memcpy(object->vertices, vertices, sizeof(vertices));

//   // update VBO
//   glBindBuffer(GL_ARRAY_BUFFER, object->VBO); // copy our vertices array in a buffer
//   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// }

void link_vertex_attributes()
{
  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);
}
