#include <SDL2/SDL.h>

#include <iostream>
#include <stack>
using namespace std;

class GameState {
	private:
		bool _isLeaving;

	protected:
		void leave();

	public:
		GameState();
		virtual void updateFrame() = 0;
		virtual void renderFrame(SDL_Renderer* renderer) = 0;
		bool isLeaving();
};

GameState::GameState()
	: _isLeaving(false) {
}

void GameState::leave() {
	_isLeaving = true;
}

bool GameState::isLeaving() {
	return _isLeaving;
}

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

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << "Unable to initialize SDL." << endl;
		return false;
	}

	if (!SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
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