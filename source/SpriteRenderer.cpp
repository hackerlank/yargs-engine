#include "SpriteRenderer.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"

#include "Utility.h"
#include "debug.h"

SpriteRenderer::SpriteRenderer(Shader& shader)
                              :shader(shader)
{
  GLuint VBO;
  GLfloat vertices[] = {
      //Pos       //TexCoords
      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f,

      0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f, 1.0f,
      1.0f, 0.0f, 1.0f, 0.0f
  };
  glGenVertexArrays(1, &this->quadVAO);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(this->quadVAO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

  //unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0); //unbind quadvao
  debug("quadVAO %d", this->quadVAO);
}


void SpriteRenderer::draw(Sprite& sprite, float x, float y, float angle, float scaleX, float scaleY)
{
  Texture2D& texture = sprite.getTexture();
  this->shader.useShader();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glm::mat4 model;

  //Translate
  model = glm::translate(model, glm::vec3(x, y, 0.0f));


  //Rotate
  model = glm::translate(model, glm::vec3(texture.width/2,
                                          texture.height/2,
                                          0.0f));
  model = glm::rotate(model, (float)glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-texture.width/2,
                                          -texture.height/2,
                                          0.0f));

  //Scale to right size
  model = glm::scale(model, glm::vec3((scaleX * texture.width),
                                      (scaleY * texture.height),
                                      1.0f));

  this->shader.setMat4("model", model);

  glActiveTexture(GL_TEXTURE0);
  texture.bind();

  glBindVertexArray(this->quadVAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0); //unbind quadVAO

  glDisable(GL_BLEND);
}

