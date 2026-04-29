CC=g++
STD=-std=c++17
CFLAGS=-Wall -Wextra
INC_PATH=-I"./libs/"
SRC=src/*.cpp \
	src/Game/*.cpp \
	src/ECS/*.cpp \
	src/AnimationManager/*.cpp \
	src/AssetManager/*.cpp \
	src/AudioManager/*.cpp \
	src/ControllerManager/*.cpp \
	src/SceneManager/*.cpp

LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 -ltinyxml2
EXEC=game_01

build:
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SRC) $(LFLAGS) -o $(EXEC)

run:
	./$(EXEC)

clean:
	rm $(EXEC)