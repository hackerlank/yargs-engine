#ifndef __PLAYERCHARACTER_H__
#define __PLAYERCHARACTER_H__

#include "Sprite.h"
#include "InputHandler.h"
#include "math/Vector2f.h"


class PlayerCharacter
{
private:
  Sprite sprite;
  Vector2f position;

public:
  PlayerCharacter(SDL_Renderer* renderer, std::string FileNamePath);
  void draw(SDL_Renderer* renderer);
  void update(float dt, InputHandler* inputHandler);

  int LeftKey;
  int RightKey;
  int DownKey;
  int UpKey;
};


#endif
