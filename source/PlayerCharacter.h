#ifndef __PLAYERCHARACTER_H__
#define __PLAYERCHARACTER_H__

#include <stdint.h>
#include "GameObject.h"
#include "SpriteRenderer.h"
#include "InputHandler.h"
#include "math/Vector2f.h"


class PlayerCharacter : public virtual GameObject
{
private:
  Sprite& sprite;
  SpriteRenderer renderer;
  Vector2f centerPosition, prevCenterPosition;
  Vector2f pos;
  Vector2f Velocity;
  double Rotation;

public:
  PlayerCharacter(Sprite& sprite, SpriteRenderer& renderer);
  void Draw(float interpolate);
  void FixedUpdate(float dt, InputHandler* inputHandler);
  void Update(float dt, InputHandler* inputHandler);
  void bindKeys(uint8_t keyLeft, uint8_t keyUp,
                uint8_t keyRight, uint8_t keyDown,
                uint8_t rotateLeftKey, uint8_t rotateRightKey);

  Vector2f getTopLeftCoords();

  Vector2f getVelocity();
  Vector2f getCenterPosition();

  uint8_t moveLeftKey;
  uint8_t moveUpKey;
  uint8_t moveRightKey;
  uint8_t moveDownKey;
  uint8_t rotateLeftKey;
  uint8_t rotateRightKey;
};


#endif
