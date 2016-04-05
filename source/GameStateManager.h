#ifndef __GAMESTATEMANAGER_H__
#define __GAMESTATEMANAGER_H__

#include <stack>

#include "GameState.h"

void pushState(std::stack<GameState*> *states, GameState* state);
void popState(std::stack<GameState*> *states);
void changeState(std::stack<GameState*> *states, GameState* state);
GameState* peekState(std::stack<GameState*> *states);

#endif
