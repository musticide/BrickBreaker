CC=g++
CXXFLAGS = -Wall -std=c++17

INCLUDE = -ISFML/include
LIBRARIES = -LSFML/lib -Lbin
LINKS = -lopengl32 -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2
DEFINES = -DSFML_STATIC

#directories
BIN=bin
INT=intermediates
SRC=src

all: game

game: $(SRC)/*.cpp
	$(CC) $(CXXFLAGS) -o bin/$@ $< $(INCLUDE) $(LIBRARIES) $(LINKS) $(DEFINES)
