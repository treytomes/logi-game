#include <SDL2/SDL.h>

#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "json.hpp"
using json = nlohmann::json;

#include "GameState.h"

#define PATH_SETTINGS "settings.json"

class Rectangle {
	private:
		int _x;
		int _y;
		int _width;
		int _height;

	public:
		Rectangle(int x, int y, int width, int height);

		int getX();
		void setX(int x);

		int getY();
		void setY(int y);

		int getWidth();
		void setWidth(int width);

		int getHeight();
		void setHeight(int height);

		int getTop();
		int getBottom();
		int getLeft();
		int getRight();

		bool contains(int x, int y);
};

Rectangle::Rectangle(int x, int y, int width, int height)
	: _x(x), _y(y), _width(width), _height(height) {
}

int Rectangle::getX() {
	return _x;
}

void Rectangle::setX(int x) {
	_x = x;
}

int Rectangle::getY() {
	return _y;
}

void Rectangle::setY(int y) {
	_y = y;
}

int Rectangle::getWidth() {
	return _width;
}

void Rectangle::setWidth(int width) {
	_width = width;
}

int Rectangle::getHeight() {
	return _height;
}

void Rectangle::setHeight(int height) {
	_height = height;
}

int Rectangle::getTop() {
	return getY();
}

int Rectangle::getBottom() {
	return getY() + getHeight() - 1;
}

int Rectangle::getLeft() {
	return getX();
}

int Rectangle::getRight() {
	return getX() + getWidth() - 1;
}

bool Rectangle::contains(int x, int y) {
	return (getLeft() <= x) && (x <= getRight()) && (getTop() <= y) && (y <= getBottom());
}

class SampleGameState: public GameState {
	private:
		bool _isDragging;
		bool _isHovering;
		Rectangle _rect;

	public:
		SampleGameState();

		void pollEvents();
		bool onKeyDown(SDL_KeyboardEvent key);
		bool onMouseButtonDown(SDL_MouseButtonEvent button);
		bool onMouseButtonUp(SDL_MouseButtonEvent button);
		bool onMouseMotion(SDL_MouseMotionEvent motion);

		void updateFrame();
		void renderFrame(SDL_Renderer* renderer);
};

SampleGameState::SampleGameState()
	: _isDragging(false), _isHovering(false), _rect(200, 200, 64, 32) {
}

bool SampleGameState::onKeyDown(SDL_KeyboardEvent key) {
	if (key.keysym.sym == SDLK_ESCAPE) {
		leave();
		return true;
	}
	return false;
}

void SampleGameState::updateFrame() {
}

void SampleGameState::renderFrame(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	if (_isDragging) {
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
	} else if (_isHovering) {
		SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
	} else {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	}

	SDL_RenderDrawLine(renderer, _rect.getLeft(), _rect.getTop(), _rect.getLeft(), _rect.getBottom());
	SDL_RenderDrawLine(renderer, _rect.getRight(), _rect.getTop(), _rect.getRight(), _rect.getBottom());
	SDL_RenderDrawLine(renderer, _rect.getLeft(), _rect.getTop(), _rect.getRight(), _rect.getTop());
	SDL_RenderDrawLine(renderer, _rect.getLeft(), _rect.getBottom(), _rect.getRight(), _rect.getBottom());
	SDL_RenderPresent(renderer);
}

bool SampleGameState::onMouseButtonDown(SDL_MouseButtonEvent button) {
	if (_isHovering) {
		_isDragging = true;
	}
	return _isHovering;
}

bool SampleGameState::onMouseButtonUp(SDL_MouseButtonEvent button) {
	_isDragging = false;
	return true;
}

bool SampleGameState::onMouseMotion(SDL_MouseMotionEvent motion) {
	_isHovering = _rect.contains(motion.x, motion.y);
	if (_isDragging) {
		_rect.setX(_rect.getX() + motion.xrel);
		_rect.setY(_rect.getY() + motion.yrel);
	}
	return _isDragging;
}

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
vector<GameState*> states;

json createSettings() {
	json settings;
	settings["graphics"]["width"] = 640;
	settings["graphics"]["height"] = 480;
	
	ofstream o("settings.json");
	o << setw(4) << settings << endl;
	return settings;
}

json getSettings() {
	ifstream f(PATH_SETTINGS);
	if (f.good()) {
		return json::parse(f);
	} else {
		return createSettings();
	}
}

bool init() {
	json settings = getSettings();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Unable to initialize SDL." << endl;
		return false;
	}

	int width = settings["graphics"]["width"].get<int>();
	int height = settings["graphics"]["height"].get<int>();
	if (!SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) == 0) {
		cerr << "Unable to create renderer." << endl;
		return false;
	}
	
	states.push_back(new SampleGameState());
	return true;
}

void shutdown() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}

	SDL_Quit();
}

void pollEvents() {
	states.back()->pollEvents();

	// Consume any events not used by the state.
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			for (vector<GameState*>::iterator iter = states.begin(); iter != states.end(); iter++) {
				(*iter)->leave();
			}
		}
	}
}

int main(int argc, char* argv[]) {
	if (!init()) {
		shutdown();
		return 1;
	}

	while (!states.empty()) {
		states.back()->updateFrame();
		states.back()->renderFrame(renderer);

		pollEvents();
		if (states.back()->isLeaving()) {
			delete states.back();
			states.pop_back();
		}
	}

	shutdown();
	return 0;
}