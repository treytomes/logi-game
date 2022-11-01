CC := g++
LD := g++ 

SRC_DIR := ./src
INCLUDE_DIR := ./include
BUILD_DIR := ./build
BIN_DIR := ./bin
LOCALE_DIR := ./locale
CFLAGS := -I $(INCLUDE_DIR) -std=c++17 -g -Wall

FLAGS_SDL2 := `sdl2-config --cflags --libs`
LIBS = $(FLAGS_SDL2) -lSDL2_ttf -lSDL2_image

MO_FILES := locale/en/LC_MESSAGES/logi-game.mo

_OBJ = main.o Border.o Circuit.o Color.o FontResource.o GameState.o Rectangle.o renderHelpers.o ResourceFactory.o
OBJ = $(patsubst %,$(BUILD_DIR)/%,$(_OBJ))

_TESTING_OBJ = testing/tests.o testing/CircuitTests.o testing/PerceptronTests.o Circuit.o CircuitFactory.o
TESTING_OBJ = $(patsubst %,$(BUILD_DIR)/%,$(_TESTING_OBJ))

all: $(BIN_DIR)/logi-game test

text:
	xgettext --keyword=_ --language=C++ --add-comments --sort-output -o locale/logi-game.pot src/main.cpp
	msgmerge --update locale/en/logi-game.po locale/logi-game.pot

$(BIN_DIR)/logi-game: $(OBJ) $(MO_FILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

locale/en/LC_MESSAGES/logi-game.mo: locale/en/logi-game.po
	msgfmt --output-file=locale/en/LC_MESSAGES/logi-game.mo locale/en/logi-game.po

test: $(BIN_DIR)/tests

$(BIN_DIR)/tests: $(TESTING_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	$(BIN_DIR)/tests

$(BUILD_DIR)/testing/%.o : $(SRC_DIR)/testing/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(BIN_DIR)/* $(BUILD_DIR)/*.o $(BUILD_DIR)/testing/*
