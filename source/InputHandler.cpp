#include "InputHandler.h"


InputHandler::InputHandler()
{
  //NOTE: pointer to internal SDL array, valid for whole lifetime, do not free
  keystate = SDL_GetKeyboardState(0);
  for(int i = 0; i < 83; i++) {
    commands[i] = new Command();
  }
}
InputHandler::~InputHandler()
{
  //TODO: Might not need if lifetime = whole program, check on later
  for(int i = 0; i < 83; i++) {
    delete commands[i];
  }
}

void InputHandler::ExecuteCommands()
{
  if(keystate[KEY_RIGHT]) {
    commands[KEY_RIGHT]->execute();
  }
  if(keystate[KEY_LEFT]) {
    commands[KEY_LEFT]->execute();
  }
  if(keystate[KEY_DOWN]) {
    commands[KEY_DOWN]->execute();
  }
  if(keystate[KEY_UP]) {
    commands[KEY_UP]->execute();
  }
  if(keystate[KEY_A]) {
    commands[KEY_A]->execute();
  }
  if(keystate[KEY_B]) {
    commands[KEY_B]->execute();
  }
}

void InputHandler::bindCommandToKey(int Key, Command* command)
{
  if(commands[Key]) {
    free(commands[Key]);
  }
  commands[Key] = command;
}

bool InputHandler::isKeyPressed(int Key)
{
  return keystate[Key];
}
