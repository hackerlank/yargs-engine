#ifndef __SPRITERENDERER_H__
#define __SPRITERENDERER_H__

#include "Shader.h"
#include "Sprite.h"


class SpriteRenderer
{
private:
  Shader& shader;
  GLuint quadVAO;


public:
  SpriteRenderer(Shader& shader);

  void draw(Sprite& sprite, float x, float y, float angle, float scaleX, float scaleY);
};

#endif
