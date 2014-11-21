CFLAGS = -Wall -pedantic -std=c99 -lm
INCS = artc_sdl2.h 
TARGET = input
SOURCES =  artc_sdl2.c $(TARGET).c displaytest.c
LIBS =  -lSDL2
CC = gcc


all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 
