GEDIR=../../src
EXEC=target
CC=g++
CFLAGS= -Wall -ansi -pedantic -std=c++11 `sdl2-config --cflags` -I$(GEDIR)
LDFLAGS= `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lSDL2_mixer
CPPFLAGS=

TARGET := $(notdir $(CURDIR))
SOURCEDIR := src 
SOURCE := $(foreach DIR,$(GEDIR),$(wildcard $(DIR)/*.cpp)) $(foreach DIR,$(SOURCEDIR),$(wildcard $(DIR)/*.cpp))

DEBUG=no
ifeq ($(DEBUG),yes)
	CPPFLAGS += -DDEBUG -g
endif


#---------------------------------------------------------------------------------

#inference
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) 

#build target
all: $(EXEC)

target: $(OBJ)
	$(CC) $(SOURCE) -o $(TARGET) $^ $(LDFLAGS) $(CFLAGS) $(CPPFLAGS)

#mingw target
mingw: LDFLAGS := -lmingw32 -static-libgcc $(LDFLAGS)
mingw: TARGET := $(TARGET).exe
mingw: $(EXEC)

#clean targets
.PHONY: clean mrproper

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(TARGET)
