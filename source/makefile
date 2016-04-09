export SOURCE_DIR=${PWD}

CC = clang++
SDL = -I${SOURCE_DIR}/../include/
SDL_LDFLAGS = -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer

#Available Debug Flags:
# DEBUG
# DEBUGDRAWVECTORS
# DEBUGSHOWFPS

CFLAGS = -Wall -Wfloat-equal -c -D DEBUG -D DEBUGDRAWVECTORS -D DEBUGSHOWFPS -O2 -std=c++11 $(SDL)

#Will be replaced
MORECFLAGS = #-Wextra -Wunreachable-code

LDFLAGS = $(SDL_LDFLAGS) -O2
EXECUTABLE = Game
BUILDDIR = ../build_mac

#<EMSCRIPTEN_FLAGS>

SOURCES = main.o Utility.o Sprite.o Vector2f.o InputHandler.o Command.o \
PlayerCharacter.o Viewport.o GameStateMain.o GameStateManager.o GameState.o \
SoundManager.o

# $< is the name of the first prereq
# $@ is the name of the target of the rule
# $^ is the name of all the prereqs

all: $(EXECUTABLE)
	@mv *.o $(EXECUTABLE) $(BUILDDIR)

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

SoundManager.o: SoundManager.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@


clean:
	@rm *.o \
	& cd $(BUILDDIR)/ && \
	rm *.o $(EXECUTABLE)
