CFLAGS = `sdl2-config --cflags` -O4 -Wall -pedantic -std=c99 -lm
INCS = ../artc_sdl2.h
TARGET = text_editor
SOURCES =  ../artc_sdl2.c $(TARGET).c 
LIBS =  `sdl2-config --libs` -lSDL2_ttf
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 
