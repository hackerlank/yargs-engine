#include "PlayerCharacter.h"
#include <math.h>
#include <cfloat>
#include "debug.h"



//NOTE: For some reason, sprite was calling its deconsructor after exiting the
//      PlayerCharacter constructor.
PlayerCharacter::PlayerCharacter(Sprite& sprite, SpriteRenderer& renderer)
                                 :sprite(sprite), renderer(renderer)
{
  centerPosition = Vector2f(80.0f,80.0f);
  prevCenterPosition = centerPosition;
  Velocity = Vector2f(0.0f, 0.0f);
  Rotation = 0;
  moveUpKey = KEY_NULL;
  moveDownKey = KEY_NULL;
  moveLeftKey = KEY_NULL;
  moveRightKey = KEY_NULL;
  rotateLeftKey = 0;
  rotateRightKey = 0;
}

void PlayerCharacter::Draw(float extrapolate)
{
  /*
  //NOTE: This uses interpolation
  Vector2f temp(prevPosition.x + interpolate*Position.x,
                prevPosition.y + interpolate*Position.y);
  sprite.draw(renderer, temp.x, temp.y);
  //NOTE: This uses nothing*/
  //sprite.draw(viewport, centerPosition.x, centerPosition.y, Rotation);
  //NOTE: This uses extrapolation

  pos = Vector2f::Lerp(prevCenterPosition, centerPosition, extrapolate);
  renderer.draw(sprite, pos.x-sprite.getWidth()/2, pos.y-sprite.getHeight()/2, Rotation, 1.0f, 1.0f);
  
  //pos = Vector2f::Lerp(prevCenterPosition, centerPosition, extrapolate);
  /*sprite.draw(viewport,
              (this->centerPosition.x + extrapolate*Velocity.x) - (float)sprite.getWidth()/2.0f,
              (this->centerPosition.y + extrapolate*Velocity.y) - (float)sprite.getHeight()/2.0f,
              Rotation);*/
/*
  #ifdef DEBUGDRAWVECTORS
  viewport->DrawDebugVector(prevCenterPosition.x
                            ,prevCenterPosition.y
                            ,pos.x
                            ,pos.y);
  #endif*/
}
float xxround(float f)
{
    return floor(f * 5 + 0.5) / 5;
    // return std::round(f * 5) / 5; // C++11
}
void PlayerCharacter::FixedUpdate(float dt, InputHandler* inputHandler)
{
  float rotationAmount = 90.0f;
  if(inputHandler->isKeyHeldDown(rotateLeftKey)) {
    Rotation -=  rotationAmount * dt;
  }
  if(inputHandler->isKeyHeldDown(rotateRightKey)) {
    Rotation +=  rotationAmount * dt;
  }

  constexpr float accelerationAmount = 200.0f;
  Vector2f Acceleration = Vector2f(0.0f,0.0f);

  if(inputHandler->isKeyHeldDown(moveLeftKey)) {
    Acceleration.x -= 1.0f;
  }
  if(inputHandler->isKeyHeldDown(moveRightKey)) {
    Acceleration.x += 1.0f;
  }
  if(inputHandler->isKeyHeldDown(moveDownKey)) {
    Acceleration.y += 1.0f;
  }
  if(inputHandler->isKeyHeldDown(moveUpKey)) {
    Acceleration.y -= 1.0f;
  }

  Acceleration.normalize();
  Acceleration = Acceleration * (accelerationAmount*dt);

  if(fabs(Acceleration.x) < FLT_EPSILON && fabs(Acceleration.y) < FLT_EPSILON) {
    if(fabs(Velocity.x) < .3f && fabs(Velocity.y) < .3f) {
      Velocity.x = 0.0f;
      Velocity.y = 0.0f;
      Acceleration.x = 0.0f;
      Acceleration.y = 0.0f;
    }
  }
  constexpr float friction = 1.0f;
  //Velocity.x += -Velocity.x * friction*dt;
  //Velocity.y += -Velocity.y * friction*dt;

  Velocity =  Acceleration;
  // Velocity.x = xxround(Velocity.x);
  // Velocity.y = xxround(Velocity.y);

  prevCenterPosition = centerPosition;
  centerPosition = centerPosition + Velocity;
}
void PlayerCharacter::Update(const float dt, InputHandler* inputHandler)
{
}

void PlayerCharacter::bindKeys(uint8_t keyLeft, uint8_t keyUp,
                               uint8_t keyRight, uint8_t keyDown,
                               uint8_t rotateLeftKey, uint8_t rotateRightKey)
{
  this->moveLeftKey = keyLeft;
  this->moveUpKey = keyUp;
  this->moveRightKey = keyRight;
  this->moveDownKey = keyDown;
  this->rotateLeftKey = rotateLeftKey;
  this->rotateRightKey = rotateRightKey;
}

Vector2f PlayerCharacter::getTopLeftCoords(){
  return Vector2f((float)this->centerPosition.x - (float)this->sprite.getWidth()/2.0f
                  ,(float)this->centerPosition.y - (float)this->sprite.getHeight()/2.0f);
}


Vector2f PlayerCharacter::getVelocity(){
    return this->Velocity;
}
Vector2f PlayerCharacter::getCenterPosition(){
    return this->pos;
}
