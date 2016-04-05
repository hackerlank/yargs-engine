#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#ifdef EMSCRIPTEN
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include <stdint.h>

#include "math/Vector2f.h"
#include "debug.h"

class Viewport
{
private:
  Vector2f CenterPosition;
  float ScreenX;
  float ScreenY;
  int ScreenWidth;
  int ScreenHeight;
  float Zoom;
//  uint8_t moveLeftKey, moveRightKey, moveUpKey, moveDownKey;
  SDL_Renderer* Renderer;
  SDL_Window* Window;

public:
    Viewport();
    Viewport(SDL_Renderer* Renderer, SDL_Window* Window);
    ~Viewport();
    void Clear();
    void Clear(int r, int g, int b, int a);
    void Present();
    void RenderToViewport(SDL_Texture* Texture, const SDL_Rect* srcRect,
                          SDL_Rect dstRect, const double angle,
                          const SDL_Point* center, const SDL_RendererFlip flip,
                          int xLocation, int yLocation);
    void PanLeft(float dt, float amount);
    void PanRight(float dt, float amount);
    void PanUp(float dt, float amount);
    void PanDown(float dt, float amount);
    void ZoomIn(float dt, float amount);
    void panBy(float dx, float dy);

    int getWidth();
    int getHeight();

    Vector2f getTopLeftCoords();
    Vector2f getBottomRightCoords();

    #ifdef DEBUGDRAWVECTORS
    void DrawDebugVector(float x1, float y1, float x2, float y2)
    {
      SDL_SetRenderDrawColor(Renderer, 255,0,0,255);
      SDL_RenderDrawLine(Renderer, (int)x1 - (int)ScreenX,
                         (int)y1 - (int)ScreenY,
                         (int)x1 - (int)ScreenX +(int)x2,
                         (int)y1 - (int)ScreenY +(int)y2);
      SDL_Rect r = { (int)x1 - (int)ScreenX +(int)x2 - 5,
                     (int)y1 - (int)ScreenY +(int)y2 - 5, 10, 10 };
      SDL_RenderFillRect(Renderer, &r);
    }
    #endif
};

#endif
