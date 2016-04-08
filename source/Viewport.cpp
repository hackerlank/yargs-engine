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
  zoomFactor = 0.5f;
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
  dstRect.x *= zoomFactor;
  dstRect.y *= zoomFactor;
  dstRect.w *=  zoomFactor;
  dstRect.h *=  zoomFactor;

  //Check if on screen
  if(dstRect.x+dstRect.w < 0 || dstRect.x > ScreenWidth) return;
  if(dstRect.y > ScreenHeight || dstRect.y+dstRect.h < 0) return;

  SDL_RenderCopyEx(Renderer, Texture, srcRect, &dstRect, angle, center, flip);

  #ifdef DEBUGDRAWVECTORS
  SDL_SetRenderDrawColor(Renderer, 255,255,0,255);
  SDL_RenderDrawRect(Renderer, &dstRect);
  #endif
}
#ifdef DEBUGDRAWVECTORS
void Viewport::DrawDebugVector(float x1, float y1, float x2, float y2)
{
  SDL_SetRenderDrawColor(Renderer, 255,0,0,255);
  SDL_RenderDrawLine(Renderer, (int)((x1-ScreenX)*zoomFactor),
                               (int)((y1-ScreenY)*zoomFactor),
                               (int)((x1-ScreenX+x2)*zoomFactor),
                               (int)((y1-ScreenY+y2)*zoomFactor)
                    );
  SDL_Rect r = { (int)((x1-ScreenX+x2-5)*zoomFactor),
                 (int)((y1-ScreenY+y2-5)*zoomFactor), 10, 10 };
  SDL_RenderFillRect(Renderer, &r);
}
#endif
void Viewport::zoomBy(float dt, float amount) {
  if((zoomFactor + dt*amount) >= ZOOM_MIN && (zoomFactor + dt*amount) <= ZOOM_MAX ){
      zoomFactor += dt*amount;
  }else{
      if(zoomFactor + dt*amount < ZOOM_MIN){
          zoomFactor = ZOOM_MIN;
      }else{
          zoomFactor = ZOOM_MAX;
      }
  }
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

float Viewport::getZoomFactor(){
    return this->zoomFactor;
}

void Viewport::setScreenCoords(int x, int y){
    this->ScreenX = x;
    this->ScreenY = y;
}

void Viewport::setZoomFactor(float z){
    this->zoomFactor = z;
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

SDL_Renderer *Viewport::getRenderer(){
    return this->Renderer;
}
