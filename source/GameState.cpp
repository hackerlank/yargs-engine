#include "GameState.h"

GameState::~GameState()
{
  //do nothing
}

GameState::GameState(Viewport *viewport){
    this->viewport = viewport;
}
