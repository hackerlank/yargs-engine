#include "PlayerCharacter.h"
#include <math.h>
#include "debug.h"

//NOTE: For some reason, sprite was calling its deconsructor after exiting the
//      PlayerCharacter constructor.
PlayerCharacter::PlayerCharacter(SDL_Renderer* renderer,
                                 std::string FileNamePath)
                                 :sprite(renderer, FileNamePath)
{
  Position = Vector2f(10,10);
  Velocity = Vector2f(0, 0);
  moveUpKey = KEY_UP;
  moveDownKey = KEY_DOWN;
  moveLeftKey = KEY_LEFT;
  moveRightKey = KEY_RIGHT;
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
  sprite.draw(renderer, Position.x + extrapolate*Velocity.x,
              Position.y + extrapolate*Velocity.y);
}

void PlayerCharacter::update(float dt, InputHandler* inputHandler)
{
  float amount = 10.0f;

  Vector2f Acceleration = Vector2f(0,0);
  if(inputHandler->isKeyPressed(moveLeftKey)) {
    Acceleration.x -= 1;
  }
  if(inputHandler->isKeyPressed(moveRightKey)) {
    Acceleration.x += 1;
  }
  if(inputHandler->isKeyPressed(moveDownKey)) {
    Acceleration.y += 1;
  }
  if(inputHandler->isKeyPressed(moveUpKey)) {
    Acceleration.y -= 1;
  }

  Acceleration.normalize();
  Acceleration = Acceleration * (amount*dt);

  if(Acceleration.getLength() == 0) {
    if(fabs(Velocity.x) < 1.0f) {
      Velocity.x = 0;
    }
    if(fabs(Velocity.y) < 1.0f) {
      Velocity.y = 0;
    }
  }

  Velocity = Velocity + Acceleration;
  Position = Position + Velocity;
}

void PlayerCharacter::bindKeys(uint8_t keyLeft, uint8_t keyUp,
                               uint8_t keyRight, uint8_t keyDown)
{
  this->moveLeftKey = keyLeft;
  this->moveUpKey = keyUp;
  this->moveRightKey = keyRight;
  this->moveDownKey = keyDown;
}
