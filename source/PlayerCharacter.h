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
  Vector2f centerPosition;
  Vector2f Velocity;
  double Rotation;

public:
  PlayerCharacter(SDL_Renderer* renderer, std::string FileNamePath);
  void Draw(Viewport* viewport, float interpolate);
  void FixedUpdate(float dt, InputHandler* inputHandler);
  void Update(float dt, InputHandler* inputHandler);
  void bindKeys(uint8_t keyLeft, uint8_t keyUp,
                uint8_t keyRight, uint8_t keyDown,
                uint8_t rotateLeftKey, uint8_t rotateRightKey);

  Vector2f getTopLeftCoords();
  bool isInViewport(Viewport* viewport, int padding);
  void panToIncludeInViewport(Viewport* viewport, int padding, float extrapolate);

  #ifdef DEBUG
  Vector2f getVelocity();
  Vector2f getCenterPosition();
  #endif

  uint8_t moveLeftKey;
  uint8_t moveUpKey;
  uint8_t moveRightKey;
  uint8_t moveDownKey;
  uint8_t rotateLeftKey;
  uint8_t rotateRightKey;
};


#endif
