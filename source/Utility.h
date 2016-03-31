#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <string>

std::string getResourcePath(const std::string& relativePath = "");

void drawText(char* message, TTF_Font *font, SDL_Renderer* Renderer,
              int x, int y);

void drawText(const std::string &message,TTF_Font* font,SDL_Renderer* Renderer,
              int x, int y);

SDL_Texture* loadTexture(std::string &FileNamePath, SDL_Renderer* Renderer);

#endif
