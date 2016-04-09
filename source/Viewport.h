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

#define ZOOM_MAX 1.0f
#define ZOOM_MIN 0.1f

class Viewport
{
private:
  Vector2f CenterPosition;
  float ScreenX;
  float ScreenY;
  int ScreenWidth;
  int ScreenHeight;
  float zoomFactor;
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
    void zoomBy(float dt, float amount);
    void setZoomFactor(float z);
    void setScreenCoords(int x, int y);
    void panBy(float dx, float dy);

    SDL_Renderer *getRenderer();

    int getWidth();
    int getHeight();

    float getZoomFactor();

    Vector2f getTopLeftCoords();
    Vector2f getBottomRightCoords();

    #ifdef DEBUGDRAWVECTORS
    void DrawDebugVector(float x1, float y1, float x2, float y2);
    #endif

};

#endif
