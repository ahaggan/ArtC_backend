CFLAGS = -Wall -pedantic -std=c99 -lm
INCS = 
TARGET = artc
SOURCES =  display.c $(TARGET).c input.c interface.c menu.c draw.c fractals.c parser.c carpet.c sierpinski.c tree.c star.c man.c interpreter.c texteditor.c
LIBS =  -lSDL2 -lSDL2_ttf
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 
