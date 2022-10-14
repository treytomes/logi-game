CC := g++
LD := g++ 
CFLAG := -Wall

SRC_DIR := ./src
BUILD_DIR := ./build
BIN_DIR := ./bin
SRC_LIST := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST := $(BUILD_DIR)/$(notdir $(SRC_LIST:.cpp=.o))

CFLAGS_SDL2 := `sdl2-config --cflags`
LIBS_SDL2 := `sdl2-config --libs`

all: logi-game

logi-game: main.o
	g++ $(BUILD_DIR)/main.o -o $(BIN_DIR)/logi-game $(CFLAGS_SDL2) $(LIBS_SDL2)

main.o:
	g++ -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

clean:
	rm -f $(BIN_DIR)/logi-game $(BUILD_DIR)/*.o
