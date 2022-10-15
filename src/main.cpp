#include <SDL2/SDL.h>

#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "json.hpp"
using json = nlohmann::json;

#include "GameState.h"

class SampleGameState: public GameState {
	public:
		void updateFrame();
		void renderFrame(SDL_Renderer* renderer);
};

void SampleGameState::updateFrame() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				leave();
			}
		}
		if (event.type == SDL_QUIT) {
			leave();
		}
	}
}

void SampleGameState::renderFrame(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
	SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
	SDL_RenderDrawLine(renderer, 340, 240, 320, 200);
	SDL_RenderPresent(renderer);
}

void updateFrame() {
}

void renderFrame(SDL_Renderer* renderer) {
}

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
stack<GameState*> states;

json createSettings() {
	json settings;
	settings["graphics"]["width"] = 640;
	settings["graphics"]["height"] = 480;
	
	ofstream o("settings.json");
	o << setw(4) << settings << endl;
	return settings;
}

#define PATH_SETTINGS "settings.json"
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
	
	states.push(new SampleGameState());
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

int main(int argc, char* argv[]) {
	if (!init()) {
		shutdown();
		return 1;
	}

	while (!states.empty()) {
		states.top()->renderFrame(renderer);
		states.top()->updateFrame();
		if (states.top()->isLeaving()) {
			delete states.top();
			states.pop();
		}
	}

	shutdown();
	return 0;
}