#ifndef __PLAYERCHARACTER_H__
#define __PLAYERCHARACTER_H__

#include <stdint.h>
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
  void bindKeys(uint8_t keyLeft, uint8_t keyUp,
                uint8_t keyRight, uint8_t keyDown);

  uint8_t LeftKey;
  uint8_t UpKey;
  uint8_t RightKey;
  uint8_t DownKey;
};


#endif
