CFLAGS = -Wall -pedantic -std=c99 -lm
INCS = 
TARGET = artc
SOURCES =  display.c $(TARGET).c input.c interface.c menu.c draw.c fractals.c manageSDL.c parser.c interpreter.c texteditor.c test_parser.c
LIBS =  -lSDL2 -lSDL2_ttf
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 
