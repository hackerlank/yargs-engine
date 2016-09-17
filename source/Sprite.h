#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Texture2D.h"

class Sprite
{
private:
  Texture2D& texture;
  int x, y, width, height;

public:
  Sprite(Texture2D& tex)
        :texture(tex)
  {
      this->texture = tex;
      this->x = 0;
      this->y = 0;
      this->width = tex.width;
      this->height = tex.height;
  }
  Sprite(Texture2D& tex, int x, int y, int w, int h)
        :texture(tex)
  {
      this->x = x;
      this->y = y;
      this->width = w;
      this->height = h;
  }



  int getWidth()
  {
    return this->texture.width;
  }
  int getHeight()
  {
    return this->texture.height;
  }

  Texture2D& getTexture()
  {
    return this->texture;
  }
  
};

#endif