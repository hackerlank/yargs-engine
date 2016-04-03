#include "PlayerCharacter.h"
#include <math.h>
#include <cfloat>
#include "debug.h"

//NOTE: For some reason, sprite was calling its deconsructor after exiting the
//      PlayerCharacter constructor.
PlayerCharacter::PlayerCharacter(SDL_Renderer* renderer,
                                 std::string FileNamePath)
                                 :sprite(renderer, FileNamePath)
{
  Position = Vector2f(10.0f,10.0f);
  Velocity = Vector2f(0.0f, 0.0f);
  Rotation = 0;
  moveUpKey = KEY_UP;
  moveDownKey = KEY_DOWN;
  moveLeftKey = KEY_LEFT;
  moveRightKey = KEY_RIGHT;
  rotateLeftKey = 0;
  rotateRightKey = 0;
}

void PlayerCharacter::draw(SDL_Renderer* renderer, float extrapolate)
{
  /*
  //NOTE: This uses interpolation
  Vector2f temp(prevPosition.x + interpolate*Position.x,
                prevPosition.y + interpolate*Position.y);
  sprite.draw(renderer, temp.x, temp.y);
  //NOTE: This uses nothing*/
  //sprite.draw(renderer, roundf(Position.x), roundf(Position.y));
  //NOTE: This uses extrapolation
  sprite.draw(renderer,
              (Position.x + extrapolate*Velocity.x) - sprite.getWidth()/2,
              (Position.y + extrapolate*Velocity.y) - sprite.getHeight()/2,
              Rotation);

  #ifdef DEBUGDRAWVECTORS
  SDL_SetRenderDrawColor(renderer, 255,0,0,255);
  SDL_RenderDrawLine(renderer, (Position.x + extrapolate*Velocity.x),
                     (Position.y + extrapolate*Velocity.y),
                     Velocity.x*15.0f+(Position.x + extrapolate*Velocity.x),
                     Velocity.y*15.0f+(Position.y + extrapolate*Velocity.y));
  #endif
}

void PlayerCharacter::update(float dt, InputHandler* inputHandler)
{
  float rotationAmount = 90.0f;
  if(inputHandler->isKeyHeldDown(rotateLeftKey)) {
    Rotation -=  rotationAmount * dt;
  }
  if(inputHandler->isKeyHeldDown(rotateRightKey)) {
    Rotation +=  rotationAmount * dt;
  }

  float amount = 10.0f;
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
  Acceleration = Acceleration * (amount*dt);

  if(fabs(Acceleration.getLength()) < FLT_EPSILON) {
    if(fabs(Velocity.x) < 1.0f) {
      Velocity.x = 0.0f;
    }
    if(fabs(Velocity.y) < 1.0f) {
      Velocity.y = 0.0f;
    }
  }

  Velocity = Velocity + Acceleration;
  Position = Position + Velocity;
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

#ifdef DEBUG
Vector2f PlayerCharacter::getVelocity(){
    return this->Velocity;
}

Vector2f PlayerCharacter::getPosition(){
    return this->Position;
}
#endif
