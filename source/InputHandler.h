#ifndef __INPUT_HANDLER_H__
#define __INPUT_HANDLER_H__

#include <SDL2/SDL.h>

#include "Command.h"
#include "Keys.h"

class InputHandler
{

//TODO(yuriy): Make InputHandler a singleton?
public:
  InputHandler();
  ~InputHandler();
  void ExecuteCommands();
  void bindCommandToKey(int Key, Command* command);
  bool isKeyPressed(int Key);

private:
  Command* commands[83];
  const Uint8* keystate;
  //const Uint8* previous_keystate;
};


#endif
