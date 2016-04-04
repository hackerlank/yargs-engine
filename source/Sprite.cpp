#include "Sprite.h"

#include "debug.h"

Sprite::Sprite()
{
  Texture = 0;
  ClippedRect.x = 0;
  ClippedRect.y = 0;
  ClippedRect.w = 0;
  ClippedRect.h = 0;
  DestRect.x = 0;
  DestRect.y = 0;
  DestRect.w = 0;
  DestRect.h = 0;
  TextureWidth = 0;
  TextureHeight = 0;
}

Sprite::Sprite(SDL_Renderer* renderer, std::string FileNamePath)
{
  Texture = 0;  //intialize to null
  this->loadTexture(renderer, FileNamePath);

  //NOTE(yuriy): By default, ClippedRect will draw the entire Texture
  ClippedRect.x = 0;
  ClippedRect.y = 0;
  ClippedRect.w = TextureWidth;
  ClippedRect.h = TextureHeight;

  DestRect.x = 0;
  DestRect.y = 0;
  DestRect.w = ClippedRect.w;
  DestRect.h = ClippedRect.h;
}

Sprite::Sprite(SDL_Renderer* renderer, std::string FileNamePath,
               int ClipX, int ClipY, int ClipWidth, int ClipHeight)
{
  Texture = 0;
  ClippedRect.x = ClipX;
  ClippedRect.y = ClipY;
  ClippedRect.w = ClipWidth;
  ClippedRect.h = ClipHeight;
  DestRect.x = 0;
  DestRect.y = 0;
  DestRect.w = ClippedRect.w;
  DestRect.h = ClippedRect.h;
  this->loadTexture(renderer, FileNamePath);
}


Sprite::~Sprite()
{
  debug("Sprite Class: Destroyed Texture");
  SDL_DestroyTexture(Texture);
}

void Sprite::draw(Viewport* viewport, int x, int y, double angle)
{

  viewport->RenderToViewport(Texture, &ClippedRect, DestRect, angle, 0, SDL_FLIP_NONE, x, y);
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
  SDL_QueryTexture(Texture, 0, 0, &TextureWidth, &TextureHeight);
}

int Sprite::getTextureWidth()
{
  return TextureWidth;
}
int Sprite::getTextureHeight()
{
  return TextureHeight;
}
int Sprite::getWidth()
{
  return ClippedRect.w;
}
int Sprite::getHeight()
{
  return ClippedRect.h;
}
int Sprite::getX()
{
  return DestRect.x;
}
int Sprite::getY()
{
  return DestRect.y;
}
