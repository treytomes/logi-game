# TODO: This rebuilds everything every time.

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
COMPILER_FLAGS := -I $(INCLUDE_DIR) -std=c++17 -g -Wall

FLAGS_SDL2 := `sdl2-config --cflags --libs`
LINKER_FLAGS = $(FLAGS_SDL2) -lSDL2_ttf -lSDL2_image

MO_FILES := locale/en/LC_MESSAGES/logi-game.mo

all: $(BIN_DIR)/logi-game $(BIN_DIR)/tests

text:
	xgettext --keyword=_ --language=C++ --add-comments --sort-output -o locale/logi-game.pot src/main.cpp
	msgmerge --update locale/en/logi-game.po locale/logi-game.pot

$(BIN_DIR)/logi-game: $(BUILD_DIR)/main.o $(BUILD_DIR)/Color.o $(BUILD_DIR)/FontResource.o $(BUILD_DIR)/GameState.o $(BUILD_DIR)/Rectangle.o $(BUILD_DIR)/ResourceFactory.o $(MO_FILES)
	g++ $(BUILD_DIR)/main.o \
		$(BUILD_DIR)/Color.o \
		$(BUILD_DIR)/FontResource.o \
		$(BUILD_DIR)/GameState.o \
		$(BUILD_DIR)/Rectangle.o \
		$(BUILD_DIR)/ResourceFactory.o \
		-o $(BIN_DIR)/logi-game $(CFLAGS_SDL2) $(LINKER_FLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp
	g++ -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o $(COMPILER_FLAGS)

$(BUILD_DIR)/Color.o: $(SRC_DIR)/Color.cpp
	g++ -c $(SRC_DIR)/Color.cpp -o $(BUILD_DIR)/Color.o $(COMPILER_FLAGS)

$(BUILD_DIR)/FontResource.o:$(SRC_DIR)/FontResource.cpp
	g++ -c $(SRC_DIR)/FontResource.cpp -o $(BUILD_DIR)/FontResource.o $(COMPILER_FLAGS)

$(BUILD_DIR)/GameState.o: $(SRC_DIR)/GameState.cpp
	g++ -c $(SRC_DIR)/GameState.cpp -o $(BUILD_DIR)/GameState.o $(COMPILER_FLAGS)

$(BUILD_DIR)/Rectangle.o: $(SRC_DIR)/Rectangle.cpp
	g++ -c $(SRC_DIR)/Rectangle.cpp -o $(BUILD_DIR)/Rectangle.o $(COMPILER_FLAGS)

$(BUILD_DIR)/ResourceFactory.o: $(SRC_DIR)/ResourceFactory.cpp
	g++ -c $(SRC_DIR)/ResourceFactory.cpp -o $(BUILD_DIR)/ResourceFactory.o $(COMPILER_FLAGS)

locale/en/LC_MESSAGES/logi-game.mo: locale/en/logi-game.po
	msgfmt --output-file=locale/en/LC_MESSAGES/logi-game.mo locale/en/logi-game.po

$(BIN_DIR)/tests: $(BUILD_DIR)/tests.o
	g++ $(BUILD_DIR)/tests.o \
		-o $(BIN_DIR)/tests $(CFLAGS_SDL2) $(LINKER_FLAGS)
	$(BIN_DIR)/tests

$(BUILD_DIR)/tests.o: $(SRC_DIR)/testing/tests.cpp
	g++ -c $(SRC_DIR)/testing/tests.cpp -o $(BUILD_DIR)/tests.o $(COMPILER_FLAGS)

clean:
	rm -f $(BIN_DIR)/logi-game $(BUILD_DIR)/*.o test/bin/logi-game-tests test/build/*.o

