#ifndef __PLAYERCHARACTER_H__
#define __PLAYERCHARACTER_H__

#include <stdint.h>
#include "GameObject.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "math/Vector2f.h"


class PlayerCharacter : public virtual GameObject
{
private:
  Sprite sprite;
  Vector2f Position;
  Vector2f Velocity;
  double Rotation;

public:
  PlayerCharacter(SDL_Renderer* renderer, std::string FileNamePath);
  void draw(SDL_Renderer* renderer, float interpolate);
  void update(float dt, InputHandler* inputHandler);
  void bindKeys(uint8_t keyLeft, uint8_t keyUp,
                uint8_t keyRight, uint8_t keyDown,
                uint8_t rotateLeftKey, uint8_t rotateRightKey);

  #ifdef DEBUG
  Vector2f getVelocity();
  Vector2f getPosition();
  #endif

  uint8_t moveLeftKey;
  uint8_t moveUpKey;
  uint8_t moveRightKey;
  uint8_t moveDownKey;
  uint8_t rotateLeftKey;
  uint8_t rotateRightKey;
};


#endif
