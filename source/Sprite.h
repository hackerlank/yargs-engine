#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "Viewport.h"
#include <string>

class Sprite
{
  SDL_Texture* Texture;
  int TextureWidth;
  int TextureHeight;
  SDL_Rect ClippedRect;
  SDL_Rect DestRect;

public:
  Sprite();
  Sprite(SDL_Renderer* renderer, std::string FileNamePath);
  Sprite(SDL_Renderer* renderer, std::string FileNamePath,
         int ClipX, int ClipY, int ClipWidth, int ClipHeight);
  ~Sprite();

  void draw(Viewport* viewport, int x, int y, double angle);
  void loadTexture(SDL_Renderer* renderer, std::string FileNamePath);

  int getTextureWidth();
  int getTextureHeight();
  int getWidth();
  int getHeight();
  int getX();
  int getY();
};

#endif
