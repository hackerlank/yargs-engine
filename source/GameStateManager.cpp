
#include "GameStateManager.h"


void pushState(std::stack<GameState*> *states, GameState* state)
{
  states->push(state);
}


//NOTE(yuriy): If you call popState from a GameState you must immediately
//             return afterwards.
void popState(std::stack<GameState*> *states)
{
  delete states->top();
  states->pop();
}

void changeState(std::stack<GameState*> *states, GameState* state)
{
  if(!states->empty()) {
    popState(states);
  }
  pushState(states, state);
}

GameState* peekState(std::stack<GameState*> *states)
{
  if(states->empty()) {
    return 0;
  }
  return states->top();
}
