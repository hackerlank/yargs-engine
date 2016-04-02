#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <string>

class Sprite
{
  SDL_Texture* Texture;
  SDL_Rect SpriteRect;

public:
  Sprite();
  Sprite(SDL_Renderer* renderer, std::string FileNamePath);
  ~Sprite();

  void draw(SDL_Renderer* renderer, int x, int y);
  void loadTexture(SDL_Renderer* renderer, std::string FileNamePath);

  int getWidth();
  int getHeight();
  int getX();
  int getY();
};

#endif
