#include "Viewport.h"

Viewport::Viewport(SDL_Renderer* Renderer, SDL_Window* Window)
{
  this->Renderer = Renderer;
  this->Window = Window;
  ScreenX = 0;
  ScreenY = 0;
  SDL_GetWindowSize(Window, &ScreenWidth, &ScreenHeight);
  CenterPosition = Vector2f(ScreenWidth/2, ScreenHeight/2);
  debug("CenterPosition (%f, %f)", CenterPosition.x ,CenterPosition.y);
}
Viewport::~Viewport()
{
  //Only use one viewport so lifetime of program?
}

void Viewport::Clear()
{
  SDL_RenderClear(Renderer);
}
void Viewport::Clear(int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
  SDL_RenderClear(Renderer);
}
void Viewport::Present()
{
  SDL_RenderPresent(Renderer);
}

void Viewport::RenderToViewport(SDL_Texture* Texture, const SDL_Rect* srcRect,
                      SDL_Rect* dstRect, const double angle,
                      const SDL_Point* center, const SDL_RendererFlip flip,
                      int xLocation, int yLocation)
{
  dstRect->x = xLocation - CenterPosition.x + ScreenWidth/2;
  dstRect->y = yLocation - CenterPosition.y + ScreenHeight/2;
  SDL_RenderCopyEx(Renderer, Texture, srcRect, dstRect, angle, center, flip);
}

void Viewport::PanLeft(float dt, float amount)
{
  CenterPosition.x -= amount*dt;
}
void Viewport::PanRight(float dt, float amount)
{
  CenterPosition.x+= amount*dt;
  ScreenX += CenterPosition.x;
}
void Viewport::PanUp(float dt, float amount)
{
  CenterPosition.y -= amount*dt;
  ScreenY -= CenterPosition.y;
}
void Viewport::PanDown(float dt, float amount)
{
  CenterPosition.y += amount*dt;
  ScreenY += CenterPosition.y;
}
