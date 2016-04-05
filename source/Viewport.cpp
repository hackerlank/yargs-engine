#include "Viewport.h"

Viewport::Viewport()
{
  Renderer = 0;
  Window = 0;
}
Viewport::Viewport(SDL_Renderer* Renderer, SDL_Window* Window)
{
  this->Renderer = Renderer;
  this->Window = Window;
  ScreenX = 0.0f;
  ScreenY = 0.0f;
  SDL_GetWindowSize(Window, &ScreenWidth, &ScreenHeight);
  CenterPosition = Vector2f(ScreenWidth/2, ScreenHeight/2);
  Zoom = 1.0f;
}
Viewport::~Viewport()
{
  //Only use one viewport so lifetime of program?
}

void Viewport::Clear()
{
  this->Clear(0, 0, 0, 255);
}
void Viewport::Clear(int r, int g, int b, int a)
{
  SDL_SetRenderDrawColor(Renderer, r, g, b, a);
  SDL_RenderClear(Renderer);
}
void Viewport::Present()
{
  SDL_RenderPresent(Renderer);
}

void Viewport::RenderToViewport(SDL_Texture* Texture, const SDL_Rect* srcRect,
                      SDL_Rect dstRect, const double angle,
                      const SDL_Point* center, const SDL_RendererFlip flip,
                      int xLocation, int yLocation)
{
  dstRect.x = xLocation - (int)ScreenX;
  dstRect.y = yLocation - (int)ScreenY;
  dstRect.w *=  Zoom;
  dstRect.h *=  Zoom;
  SDL_RenderCopyEx(Renderer, Texture, srcRect, &dstRect, angle, center, flip);
  #ifdef DEBUGDRAWVECTORS
  SDL_SetRenderDrawColor(Renderer, 255,255,0,255);
  SDL_RenderDrawRect(Renderer, &dstRect);
  #endif
}

void Viewport::ZoomIn(float dt, float amount) {
  Zoom += dt*amount;
}

void Viewport::PanLeft(float dt, float amount)
{
  ScreenX -= amount*dt;
  CenterPosition.x -= amount*dt;
}
void Viewport::PanRight(float dt, float amount)
{
  ScreenX += amount*dt;
  CenterPosition.x += amount*dt;
}
void Viewport::PanUp(float dt, float amount)
{
  ScreenY -= amount*dt;
  CenterPosition.y -= amount*dt;
}
void Viewport::PanDown(float dt, float amount)
{
  ScreenY += amount*dt;
  CenterPosition.y += amount*dt;
}

int Viewport::getWidth()
{
    return this->ScreenWidth;
}

int Viewport::getHeight()
{
    return this->ScreenHeight;
}

void Viewport::panBy(float dx, float dy)
{
    ScreenX += dx;
    ScreenY += dy;
    CenterPosition = Vector2f((ScreenWidth+ScreenX)/2, (ScreenHeight+ScreenY));
}

Vector2f Viewport::getTopLeftCoords()
{
    return Vector2f(this->ScreenX, this->ScreenY);
}
Vector2f Viewport::getBottomRightCoords()
{
    return Vector2f(this->ScreenX + (float)this->ScreenWidth,
                    this->ScreenY + (float)this->ScreenHeight);
}
