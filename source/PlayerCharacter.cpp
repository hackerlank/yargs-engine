#include "PlayerCharacter.h"
#include <math.h>
#include <cfloat>
#include "debug.h"


PlayerCharacter::PlayerCharacter()
{
  Rotation = 0;
}

//NOTE: For some reason, sprite was calling its deconsructor after exiting the
//      PlayerCharacter constructor.
PlayerCharacter::PlayerCharacter(SDL_Renderer* renderer,
                                 std::string FileNamePath)
                                 :sprite(renderer, FileNamePath)
{
  centerPosition = Vector2f(80.0f,80.0f);
  Velocity = Vector2f(0.0f, 0.0f);
  Rotation = 0;
  moveUpKey = KEY_NULL;
  moveDownKey = KEY_NULL;
  moveLeftKey = KEY_NULL;
  moveRightKey = KEY_NULL;
  rotateLeftKey = 0;
  rotateRightKey = 0;
}

void PlayerCharacter::Draw(Viewport* viewport, float extrapolate)
{
  /*
  //NOTE: This uses interpolation
  Vector2f temp(prevPosition.x + interpolate*Position.x,
                prevPosition.y + interpolate*Position.y);
  sprite.draw(renderer, temp.x, temp.y);
  //NOTE: This uses nothing*/
  //sprite.draw(renderer, roundf(Position.x), roundf(Position.y));
  //NOTE: This uses extrapolation
  sprite.draw(viewport,
              (this->centerPosition.x + extrapolate*Velocity.x) - sprite.getWidth()/2.0f,
              (this->centerPosition.y + extrapolate*Velocity.y) - sprite.getHeight()/2.0f,
              Rotation);

  #ifdef DEBUGDRAWVECTORS
  viewport->DrawDebugVector( this->centerPosition.x + extrapolate*Velocity.x
                             ,this->centerPosition.y + extrapolate*Velocity.y
                             ,Velocity.x*15.0f
                             ,Velocity.y*15.0f);
  #endif
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

  constexpr float accelerationAmount = 10.0f;
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
    if(fabs(Velocity.x) < .2f && fabs(Velocity.y) < .2f) {
      Velocity.x = 0.0f;
      Velocity.y = 0.0f;
    }
  }
  constexpr float friction = 1.0f;
  Velocity.x += -Velocity.x * friction*dt;
  Velocity.y += -Velocity.y * friction*dt;

  Velocity = Velocity + Acceleration;
  this->centerPosition = this->centerPosition + Velocity;
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
    return  Vector2f((float)this->centerPosition.x - (float)this->sprite.getWidth()/2.0f
                   , (float)this->centerPosition.y - (float)this->sprite.getHeight()/2.0f);
}

bool PlayerCharacter::isInViewport(Viewport* viewport, int padding)
{
    //TODO: Take into account the zoom factor
    Vector2f charTL = this->getTopLeftCoords();
    Vector2f dimensions = Vector2f(this->sprite.getWidth(), this->sprite.getHeight());
    Vector2f charBR = charTL;
    charBR.x += (dimensions.x);
    charBR.y += (dimensions.y);

    Vector2f vpTL = viewport->getTopLeftCoords();
    Vector2f vpBR = viewport->getBottomRightCoords();

    bool isInViewport = true;

    isInViewport = isInViewport && vpTL.x + (float)padding < charTL.x; //not on the left of the viewport
    if(viewport->getWidth() >= dimensions.x){ //IF character can completely fit width-wise
        isInViewport = isInViewport && charBR.x + (float)padding < vpBR.x; //ending x not exceeding viewport width
    }

    isInViewport = isInViewport && vpTL.y + (float)padding < charTL.y; //not on top of the viewport
    if(viewport->getHeight() >= dimensions.y){ //IF character can completely fit height-wise
        isInViewport = isInViewport && charBR.y + (float)padding < vpBR.y; //ending y not exceeding viewport height
    }

    //debug("isInViewport = %d\n", isInViewport);

    return isInViewport;
}

void PlayerCharacter::panToIncludeInViewport(Viewport* viewport, int padding, float extrapolate)
{
    if(!this->isInViewport(viewport, padding)){
        //TODO: Take into account the zoom factor
        Vector2f charTL = this->getTopLeftCoords();
        Vector2f dimensions = Vector2f(this->sprite.getWidth(), this->sprite.getHeight());
        Vector2f charBR = charTL;
        charBR.x += (dimensions.x);
        charBR.y += (dimensions.y);

        Vector2f vpTL = viewport->getTopLeftCoords();
        Vector2f vpBR = viewport->getBottomRightCoords();

        Vector2f diff;
        //Handle x
        if(!(vpTL.x + (float)padding < charTL.x)) //on the left of the viewport
        {
            diff.x = charTL.x - vpTL.x - (float)padding;
        }else if(viewport->getWidth() >= dimensions.x){ //IF character can completely fit width-wise
            if( !(charBR.x + (float)padding < vpBR.x)  ) //ending x exceeding viewport width
            {
                diff.x = charBR.x - vpBR.x + (float)padding;
            }
        }
        //Handle y
        if(!(vpTL.y + (float)padding < charTL.y)) // on top of the viewport
        {
            diff.y = charTL.y - vpTL.y - (float)padding;
        }else if(viewport->getHeight() >= dimensions.y){ //IF character can completely fit height-wise
            if( !(charBR.y + (float)padding < vpBR.y)  ) //ending y exceeding viewport height
            {
                diff.y = charBR.y - vpBR.y + (float)padding;
            }
        }

        viewport->panBy(diff.x + extrapolate*Velocity.x, diff.y + extrapolate*Velocity.y);
    }

}

#ifdef DEBUG
Vector2f PlayerCharacter::getVelocity(){
    return this->Velocity;
}
Vector2f PlayerCharacter::getCenterPosition(){
    return this->centerPosition;
}
#endif
