#include "PlayerCharacter.h"
#include "debug.h"

PlayerCharacter::PlayerCharacter(SDL_Renderer* renderer,
                                 std::string FileNamePath)
                                 :sprite(renderer, FileNamePath)
{
  position = Vector2f(10,10);
  UpKey = KEY_UP;
  DownKey = KEY_DOWN;
  LeftKey = KEY_LEFT;
  RightKey = KEY_RIGHT;
}

void PlayerCharacter::draw(SDL_Renderer* renderer)
{
  sprite.draw(renderer, position.x, position.y);
}

void PlayerCharacter::update(float dt, InputHandler* inputHandler)
{
  float amount = 200.0f;

  if(inputHandler->isKeyPressed(LeftKey)) {
    position.x = position.x - amount*dt;
  }
  if(inputHandler->isKeyPressed(RightKey)) {
    position.x = position.x + amount*dt;
  }
  if(inputHandler->isKeyPressed(DownKey)) {
    position.y = position.y + amount*dt;
  }
  if(inputHandler->isKeyPressed(UpKey)) {
    position.y = position.y - amount*dt;
  }
}

void PlayerCharacter::bindKeys(uint8_t keyLeft, uint8_t keyUp,
                               uint8_t keyRight, uint8_t keyDown)
{
  this->LeftKey = keyLeft;
  this->UpKey = keyUp;
  this->RightKey = keyRight;
  this->DownKey = keyDown;
}
