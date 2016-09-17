#include <math.h>
#include <cfloat>

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
  //Only use one viewport so lifetime of program? No need to free stuff?
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
float fdround(float f)
{
    return floor(f * 5 + 0.5) / 5;
    // return std::round(f * 5) / 5; // C++11
}
void Viewport::RenderToViewport(SDL_Texture* Texture, const SDL_Rect* srcRect,
                      SDL_Rect dstRect, const double angle,
                      const SDL_Point* center, const SDL_RendererFlip flip,
                      float xLocation, float yLocation)
{
  //debug("float xLoc: %f, float ScreenX: %f", xLocation, ScreenX);
  //debug("xLocation: %d, ScreenX: %d", (int)xLocation, (int)ScreenX);
  dstRect.x = (int)((double)(xLocation) - (double)(ScreenX));
  dstRect.y = (int)((double)(yLocation) - (double)(ScreenY));
  //debug("Draw at %d, %d", dstRect.x, dstRect.y);
  dstRect.w *=  Zoom;
  dstRect.h *=  Zoom;

  //Check if on screen
  if(dstRect.x+dstRect.w < 0 || dstRect.x > ScreenWidth) return;
  if(dstRect.y > ScreenHeight || dstRect.y+dstRect.h < 0) return;

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
    CenterPosition = Vector2f((ScreenWidth+ScreenX)/2.0f, (ScreenHeight+ScreenY));
}
float tround(float f)
{
    //return floor(f * 5 + 0.5) / 5;
    return (roundf(f * 32.0f)/32.0f);
    // return std::round(f * 5) / 5; // C++11
}
void Viewport::followTarget(Vector2f target, float dt)
{
  target.x = target.x-ScreenWidth/2;
  target.y = target.y-ScreenHeight/2;
  debug("Target %f, %f", target.x, target.y);
  //target.x = (int) target.x;
  //target.y = (int) target.y;

  Vector2f camPos = Vector2f(ScreenX, ScreenY);
  Vector2f pos = Vector2f::Lerp(camPos, target, 4.0f*dt);
  //if(fabs(camPos.x-target.x) < .5f && fabs(camPos.y-target.y) < .5f) return;
  //ScreenX = target.x;
  //ScreenY = target.y;*/

  float N = 15.0f;
  ScreenX = ((ScreenX*(N-1.0f)) + target.x) / N;
  ScreenY = ((ScreenY*(N-1.0f)) + target.y) / N;
  //ScreenX = tround(ScreenX);
  //ScreenY = tround(ScreenY);
  //ScreenX = (int)pos.x;
  //ScreenY = (int)pos.y;
  // if(fabs(ScreenX-target.x) > 1.0f || fabs(ScreenY-target.y) > 1.0f){
  //   //debug("test %f", fabs(ScreenX-target.x));
  //   ScreenX = pos.x;
  //   ScreenY = pos.y;
  // }
  // else {
  //   ScreenX = target.x;
  //   ScreenY = target.y;
  // }
  //ScreenX = target.x;
  //ScreenY = target.y;

  debug("CamPosx:%f CamPosy:%f", ScreenX, ScreenY);
  //CenterPosition = Vector2f((ScreenWidth+ScreenX)/2.0f, (ScreenHeight+ScreenY));
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
