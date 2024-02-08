CXXFLAGS = -Wall -std=c++17

INCLUDE = -ISFML/include
LIBRARIES = -LSFML/lib -Lbin
LINKS = -lopengl32 -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2
DEFINES = -DSFML_STATIC

all:
	g++ $(CXXFLAGS) -o bin/game main.cpp $(INCLUDE) $(LIBRARIES) $(LINKS) $(DEFINES)
