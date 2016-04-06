CC = em++
SDL = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2  \
-s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets/alienGreen.png \
--preload-file assets/blackline.png --preload-file assets/grass.png \
--preload-file assets/fonts/consola.ttf \
--preload-file assets/background.png \
--preload-file assets/dirt.png

CFLAGS = -c -D DEBUG -D DEBUGDRAWVECTORS -s USE_SDL=2 -s \
USE_SDL_IMAGE=1 -s USE_SDL_TTF=2  -s SDL2_IMAGE_FORMATS='["png"]' -D EMSCRIPTEN -O2 -std=c++11

MORECFLAGS = #-Wextra -Wunreachable-code

LDFLAGS = $(SDL) --emrun
EXECUTABLE = Game.html
BUILDDIR = ../build

SOURCES = main.o Utility.o Sprite.o Vector2f.o InputHandler.o Command.o \
PlayerCharacter.o Viewport.o GameStateMain.o GameStateManager.o GameState.o

# $< is the name of the first prereq
# $@ is the name of the target of the rule
# $^ is the name of all the prereqs

all: $(EXECUTABLE)
	echo "Nothing" #@mv *.o $(EXECUTABLE) $(BUILDDIR)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(LDFLAGS) $^ -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

GameStateMain.o: GameStateMain.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

GameStateManager.o: GameStateManager.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

GameState.o: GameState.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

PlayerCharacter.o: PlayerCharacter.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Viewport.o: Viewport.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

InputHandler.o: InputHandler.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Command.o: Command.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Utility.o: Utility.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Sprite.o: Sprite.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Vector2f.o: math/Vector2f.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@


clean:
	rm *.o Game.html Game.js Game.data *.bc
