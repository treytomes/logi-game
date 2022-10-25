CC := g++
LD := g++ 
CFLAG := -Wall

SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
BIN_DIR := ./bin
LOCALE_DIR := ./locale
SRC_LIST := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST := $(BUILD_DIR)/$(notdir $(SRC_LIST:.cpp=.o))
COMPILER_FLAGS := $(INCLUDE_DIR) -std=c++17 -g -Wall

FLAGS_SDL2 := `sdl2-config --cflags --libs`
LINKER_FLAGS = $(FLAGS_SDL2) -lSDL2_ttf -lSDL2_image

all: logi-game

test: logi-game-tests

text:
	xgettext --keyword=_ --language=C++ --add-comments --sort-output -o locale/logi-game.pot src/main.cpp
	msgmerge --update locale/en/logi-game.po locale/logi-game.pot

logi-game: main.o Color.o FontResource.o GameState.o Rectangle.o ResourceFactory.o logi-game.mo
	g++ $(BUILD_DIR)/main.o \
		$(BUILD_DIR)/Color.o \
		$(BUILD_DIR)/FontResource.o \
		$(BUILD_DIR)/GameState.o \
		$(BUILD_DIR)/Rectangle.o \
		$(BUILD_DIR)/ResourceFactory.o \
		-o $(BIN_DIR)/logi-game $(CFLAGS_SDL2) $(LINKER_FLAGS)

main.o:
	g++ -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o -I $(COMPILER_FLAGS)

Color.o:
	g++ -c $(SRC_DIR)/Color.cpp -o $(BUILD_DIR)/Color.o -I $(COMPILER_FLAGS)

FontResource.o:
	g++ -c $(SRC_DIR)/FontResource.cpp -o $(BUILD_DIR)/FontResource.o -I $(COMPILER_FLAGS)

GameState.o:
	g++ -c $(SRC_DIR)/GameState.cpp -o $(BUILD_DIR)/GameState.o -I $(COMPILER_FLAGS)

Rectangle.o:
	g++ -c $(SRC_DIR)/Rectangle.cpp -o $(BUILD_DIR)/Rectangle.o -I $(COMPILER_FLAGS)

ResourceFactory.o:
	g++ -c $(SRC_DIR)/ResourceFactory.cpp -o $(BUILD_DIR)/ResourceFactory.o -I $(COMPILER_FLAGS)

logi-game.mo:
	msgfmt --output-file=locale/en/LC_MESSAGES/logi-game.mo locale/en/logi-game.po

logi-game-tests: test/src/main.o
	g++ test/build/main.o \
		-o test/bin/logi-game-tests $(CFLAGS_SDL2) $(LINKER_FLAGS)
	test/bin/logi-game-tests

test/src/main.o:
	g++ -c test/src/main.cpp -o test/build/main.o -I $(COMPILER_FLAGS)

clean:
	rm -f $(BIN_DIR)/logi-game $(BUILD_DIR)/*.o test/bin/logi-game-tests test/build/*.o

