CC := g++
LD := g++ 
CFLAG := -Wall

SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
BIN_DIR := ./bin
SRC_LIST := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST := $(BUILD_DIR)/$(notdir $(SRC_LIST:.cpp=.o))
COMPILER_FLAGS := $(INCLUDE_DIR) -std=c++11

FLAGS_SDL2 := `sdl2-config --cflags --libs`
LINKER_FLAGS = $(FLAGS_SDL2)

all: logi-game

logi-game: main.o GameState.o
	g++ $(BUILD_DIR)/main.o $(BUILD_DIR)/GameState.o -o $(BIN_DIR)/logi-game $(CFLAGS_SDL2) $(LINKER_FLAGS)

main.o:
	g++ -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o -I $(COMPILER_FLAGS)

GameState.o:
	g++ -c $(SRC_DIR)/GameState.cpp -o $(BUILD_DIR)/GameState.o -I $(COMPILER_FLAGS)

clean:
	rm -f $(BIN_DIR)/logi-game $(BUILD_DIR)/*.o
