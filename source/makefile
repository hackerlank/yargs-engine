CC = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf

CFLAGS = -Wall -c -DDEBUG -std=c++11
LDFLAGS = $(SDL)
EXECUTABLE = Game
BUILDDIR = ../build


# $< is the name of the first prereq
# $@ is the name of the target of the rule
# $^ is the name of all the prereqs

all: $(EXECUTABLE)
	@mv *.o $(EXECUTABLE) $(BUILDDIR)

$(EXECUTABLE): main.o Utility.o Sprite.o Vector2f.o InputHandler.o Command.o
	$(CC) $(LDFLAGS) $^ -o $@

main.o: main.cpp
	$(CC) $(CFLAGS) $< -o $@

InputHandler.o: InputHandler.cpp
	$(CC) $(CFLAGS) $< -o $@

Command.o: Command.cpp
	$(CC) $(CFLAGS) $< -o $@

Utility.o: Utility.cpp
	$(CC) $(CFLAGS) $< -o $@

Sprite.o: Sprite.cpp
	$(CC) $(CFLAGS) $< -o $@

Vector2f.o: math/Vector2f.cpp
	$(CC) $(CFLAGS) $< -o $@


clean:
	@rm *.o \
	& cd $(BUILDDIR)/ && \
	rm *.o $(EXECUTABLE)
