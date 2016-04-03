#include "Sprite.h"

#include "debug.h"

Sprite::Sprite()
{
  Texture = 0;
  SpriteRect.x = 0.;
  SpriteRect.y = 0;
  SpriteRect.w = 0;
  SpriteRect.h = 0;
}

Sprite::Sprite(SDL_Renderer* renderer, std::string FileNamePath)
{
  Texture = 0;  //intialize to null
  this->loadTexture(renderer, FileNamePath);
}

Sprite::~Sprite()
{
  SDL_DestroyTexture(Texture);
}

void Sprite::draw(SDL_Renderer* renderer, int x, int y)
{
  SpriteRect.x = x;
  SpriteRect.y = y;
  SDL_RenderCopy(renderer, Texture, 0, &SpriteRect);
}

void Sprite::loadTexture(SDL_Renderer* renderer, std::string FileNamePath)
{
  if(Texture) {
    debug("Sprite Class: Destroyed Texture");
    SDL_DestroyTexture(Texture);
  }
  Texture = IMG_LoadTexture(renderer, FileNamePath.c_str());
  if(!Texture) {
    debugSDL();
    return;
  }
  debug("Sprite Class: Loaded Texture");
  SDL_QueryTexture(Texture, 0, 0, &SpriteRect.w, &SpriteRect.h);
  SpriteRect.x = 0;
  SpriteRect.y = 0;
  this->draw(renderer, 10, 10);
}

int Sprite::getWidth()
{
  return SpriteRect.w;
}
int Sprite::getHeight()
{
  return SpriteRect.h;
}
int Sprite::getX()
{
  return SpriteRect.x;
}
int Sprite::getY()
{
  return SpriteRect.y;
}
