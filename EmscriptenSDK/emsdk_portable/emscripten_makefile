CC = em++
SDL = -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2  \
-s SDL2_IMAGE_FORMATS='["png"]' --preload-file assets/alienGreen.png \
--preload-file assets/blackline.png --preload-file assets/grass.png --preload-file assets/fonts/consola.ttf -O2

CFLAGS = -c -D DEBUG -D DEBUGDRAWVECTORS -s USE_SDL=2 -s \
USE_SDL_IMAGE=2 -s USE_SDL_TTF=2  -s SDL2_IMAGE_FORMATS='["png"]' -D EMSCRIPTEN -O2

MORECFLAGS = #-Wextra -Wunreachable-code

LDFLAGS = $(SDL) --emrun
EXECUTABLE = Game.html
BUILDDIR = ../build

SOURCES = main.bc Utility.bc Sprite.bc Vector2f.bc InputHandler.bc Command.bc \
PlayerCharacter.bc Viewport.bc

# $< is the name of the first prereq
# $@ is the name of the target of the rule
# $^ is the name of all the prereqs

all: $(EXECUTABLE)
	echo "Nothing" #@mv *.o $(EXECUTABLE) $(BUILDDIR)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(LDFLAGS) $^ -o $(EXECUTABLE)

main.bc: main.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

PlayerCharacter.bc: PlayerCharacter.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Viewport.bc: Viewport.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

InputHandler.bc: InputHandler.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Command.bc: Command.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Utility.bc: Utility.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Sprite.bc: Sprite.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Vector2f.bc: math/Vector2f.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@


clean:
	rm *.o Game.html Game.js Game.data *.bc
