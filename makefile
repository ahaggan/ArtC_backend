CFLAGS = -Wall -pedantic -std=c99 -lm
INCS = artc_sdl2.h 
TARGET = artc_integrated_v1
SOURCES =  artc_sdl2.c $(TARGET).c draw_integrated_v1.c input_integrated_v1.c fractals.c
LIBS =  -lSDL2 -lSDL2_ttf
CC = gcc

all: $(TARGET)

$(TARGET): $(SOURCES) $(INCS)
	$(CC) $(SOURCES) -o $(TARGET) $(CFLAGS) $(LIBS)

clean:
	rm -f $(TARGET)

run: all
	$(TARGET) 
