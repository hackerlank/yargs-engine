#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>

#include "Utility.h"
#include "debug.h"


std::string getResourcePath(const std::string& relativePath)
{
	#ifdef _WIN32
	#define PATH_SEP '\\'
	#else
	#define PATH_SEP '/'
	#endif

	static std::string assetBasePath; //keep static to avoid recalculating
	if(assetBasePath.empty()) {
		char *basePath = SDL_GetBasePath();
		if (basePath){
			assetBasePath = basePath;
			SDL_free(basePath);
		}
		else {
			debugSDL();
			return "";
		}
		size_t pos = assetBasePath.rfind("build");
		assetBasePath = assetBasePath.substr(0, pos) + "assets" + PATH_SEP;
	}
	return assetBasePath + relativePath;
}

void drawText(char* message, TTF_Font *font, SDL_Renderer* Renderer)
{
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Rect fRect;
	fRect.x = 10;
	fRect.y = 10;
	SDL_Surface* surface = TTF_RenderText_Blended(font, message, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer, surface);
	SDL_QueryTexture(texture, 0, 0, &fRect.w, &fRect.h);
	SDL_RenderCopy(Renderer, texture, 0, &fRect);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void drawText(const std::string &message,TTF_Font* font,SDL_Renderer* Renderer)
{
	drawText(message.c_str(), font, Renderer);
}


SDL_Texture* loadTexture(std::string &FileNamePath, SDL_Renderer* Renderer)
{
	SDL_Texture* Texture = IMG_LoadTexture(Renderer, FileNamePath.c_str());
	if(!Texture) {
		debugSDL();
	}
	return Texture;
}
