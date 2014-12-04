CFLAGS = -Wall -pedantic -std=c99 -lm
INCS = display.h input.h artc.h parser.h test.h
TARGET = interface
SOURCES =  display.c $(TARGET).c draw.c fractals.c input.c parser.c carpet.c test.c sierpinski.c tree.c
LIBS =  -lSDL2 -lSDL2_ttf
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 
