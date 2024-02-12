CC=g++
CXXFLAGS = -Wall -std=c++17
PWSH=@pwsh -NoProfile -Command

INCLUDE = -ISFML/include
LIBRARIES = -LSFML/lib -Lbin
LINKS = -lopengl32 -lsfml-graphics-2 -lsfml-window-2 -lsfml-system-2
DEFINES = -DSFML_STATIC

#directories
BIN=bin
INT=intermediates
SRC=src

all: game
	@echo Staring game.exe...
	$(PWSH) ".\bin\game.exe"

game: $(SRC)/*.cpp
	@echo Building game.exe...
	@$(CC) $(CXXFLAGS) -o bin/$@ $< $(INCLUDE) $(LIBRARIES) $(LINKS) $(DEFINES)
	@echo Built game.exe
