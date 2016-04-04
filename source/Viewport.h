#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__

#include <SDL2/SDL.h>
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
                          SDL_Rect* dstRect, const double angle,
                          const SDL_Point* center, const SDL_RendererFlip flip,
                          int xLocation, int yLocation);
    void PanLeft(float dt, float amount);
    void PanRight(float dt, float amount);
    void PanUp(float dt, float amount);
    void PanDown(float dt, float amount);

    #ifdef DEBUGDRAWVECTORS
    void DrawDebugVector(int x1, int y1, int x2, int y2)
    {
      SDL_SetRenderDrawColor(Renderer, 255,0,0,255);
      SDL_RenderDrawLine(Renderer, x1 - CenterPosition.x + ScreenWidth/2,
                         y1 - CenterPosition.y + ScreenHeight/2,
                         x2 - CenterPosition.x + ScreenWidth/2,
                         y2 - CenterPosition.y + ScreenHeight/2);
    }
    #endif
};

#endif
