#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <string>

std::string getResourcePath(const std::string& relativePath = "");

void drawText(char* message, TTF_Font *font, SDL_Renderer* Renderer);

void drawText(const std::string &message,TTF_Font* font,SDL_Renderer* Renderer);

SDL_Texture* loadTexture(std::string &FileNamePath, SDL_Renderer* Renderer);

#endif
