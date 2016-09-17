CC = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf

CFLAGS = -Wall -Wfloat-equal -c -D DEBUG -D DEBUGDRAWVECTORS -O2 -std=c++11

#Will be replaced
MORECFLAGS = #-Wextra -Wunreachable-code

LDFLAGS = $(SDL) -L/usr/local/lib /usr/local/opt/glew/lib/libGLEW.a  -framework Cocoa \
-framework OpenGL -framework IOKit -framework CoreVideo
EXECUTABLE = Game
BUILDDIR = ../build_mac

#<EMSCRIPTEN_FLAGS>

SOURCES = main.o Shader.o Utility.o Texture2D.o SpriteRenderer.o GameStateMain.o \
GameStateManager.o GameState.o PlayerCharacter.o InputHandler.o Vector2f.o \
Camera.o

# $< is the name of the first prereq
# $@ is the name of the target of the rule
# $^ is the name of all the prereqs

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(LDFLAGS) $^ -o $(BUILDDIR)/$(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Shader.o: Shader.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Utility.o: Utility.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Texture2D.o: Texture2D.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

SpriteRenderer.o: SpriteRenderer.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@



GameStateMain.o: GameStateMain.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

GameStateManager.o: GameStateManager.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

GameState.o: GameState.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

PlayerCharacter.o: PlayerCharacter.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

InputHandler.o: InputHandler.cpp
		$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Vector2f.o: math/Vector2f.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@

Camera.o: Camera.cpp
	$(CC) $(CFLAGS) $(MORECFLAGS) $< -o $@


.PHONY: clean play
clean:
	@rm *.o \
	& cd $(BUILDDIR)/ && \
	rm *.o $(EXECUTABLE)

play:
	$(BUILDDIR)/$(EXECUTABLE)
