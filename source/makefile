CC = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf

CFLAGS = -Wall -Wfloat-equal -c -D DEBUG -D DEBUGDRAWVECTORS -O2

MORECFLAGS = #-Wextra -Wunreachable-code

LDFLAGS = $(SDL) -O2
EXECUTABLE = Game
BUILDDIR = ../build

SOURCES = main.o Utility.o Sprite.o Vector2f.o InputHandler.o Command.o \
PlayerCharacter.o Viewport.o

# $< is the name of the first prereq
# $@ is the name of the target of the rule
# $^ is the name of all the prereqs

all: $(EXECUTABLE)
	@mv *.o $(EXECUTABLE) $(BUILDDIR)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(LDFLAGS) $^ -o $(EXECUTABLE)

main.o: main.cpp
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
	@rm *.o \
	& cd $(BUILDDIR)/ && \
	rm *.o $(EXECUTABLE)
