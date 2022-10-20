#include <libintl.h>
#include <locale.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <stack>
#include <fstream>
using namespace std;

#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "json.hpp"
using json = nlohmann::json;

#include "GameState.h"
#include "Rectangle.h"

#define _(STRING) gettext(STRING)

#define PATH_SETTINGS "settings.json"

class SampleGameState: public GameState {
	private:
		bool _isDragging;
		bool _isHovering;
		Rectangle _rect;
		TTF_Font* _font;
		SDL_Texture* _texture;

	public:
		SampleGameState();
		~SampleGameState();

		void pollEvents();
		bool onKeyDown(SDL_KeyboardEvent key);
		bool onMouseButtonDown(SDL_MouseButtonEvent button);
		bool onMouseButtonUp(SDL_MouseButtonEvent button);
		bool onMouseMotion(SDL_MouseMotionEvent motion);

		void enter(SDL_Renderer* renderer);
		void updateFrame();
		void renderFrame(SDL_Renderer* renderer);
};

SampleGameState::SampleGameState()
	: _isDragging(false), _isHovering(false), _rect(200, 200, 64, 32) {
	_font = TTF_OpenFont("./assets/fonts/UbuntuMono/UbuntuMono-Regular.ttf", 16);
	if (!_font) {
		cerr << _("Error loading font: ") << TTF_GetError() << endl;
	}
}

SampleGameState::~SampleGameState() {
	TTF_CloseFont(_font);
	_font = nullptr;

	SDL_DestroyTexture(_texture);
	_texture = nullptr;
}

bool SampleGameState::onKeyDown(SDL_KeyboardEvent key) {
	if (key.keysym.sym == SDLK_ESCAPE) {
		leave();
		return true;
	}
	return false;
}

void SampleGameState::enter(SDL_Renderer* renderer) {
	SDL_Surface* buffer = IMG_Load("./assets/bootstrap-icons-1.9.1/alarm-fill.svg");
	if (!buffer) {
		cerr << _("Error loading image alarm.svg: ") << SDL_GetError() << endl;
	}

	_texture = SDL_CreateTextureFromSurface(renderer, buffer);
	SDL_FreeSurface(buffer);
	if (!_texture) {
		cerr << _("Error creating texture: ") << SDL_GetError() << endl;
	}
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

	SDL_Color textColor;
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	textColor.a = 255;

	SDL_Surface* textSurface = TTF_RenderText_Solid(_font, _("Hello, world!"), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	SDL_Rect dest;
	dest.x = 320 - (textSurface->w / 2.0f);
	dest.y = 240;
	dest.w = textSurface->w;
	dest.h = textSurface->h;
	SDL_RenderCopy(renderer, textTexture, NULL, &dest);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);

	dest.x = 100;
	dest.y = 100;
	dest.w = 16;
	dest.h = 16;
	SDL_SetTextureColorMod(_texture, 255, 0, 255);
	SDL_RenderCopy(renderer, _texture, NULL, &dest);

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

	/* Setting the i18n environment */
	setlocale(LC_ALL, "");
	bindtextdomain("logi-game", "./locale");
	textdomain("logi-game");

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << _("Unable to initialize SDL: ") << SDL_GetError() << endl;
		return false;
	}

	int width = settings["graphics"]["width"].get<int>();
	int height = settings["graphics"]["height"].get<int>();
	if (!SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) == 0) {
		cerr << _("Unable to create renderer: ") << SDL_GetError() << endl;
		return false;
	}
	
	if (IMG_Init(IMG_INIT_PNG) < 0) {
		cerr << _("Error initializing SDL_image: ") << IMG_GetError() << endl;
		return false;
	}

	if (TTF_Init() < 0) {
		cerr << _("Error intializing SDL_ttf: ") << TTF_GetError() << endl;
		return false;
	}

	states.push_back(new SampleGameState());
	states.back()->enter(renderer);
	return true;
}

void shutdown() {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}

	TTF_Quit();
	IMG_Quit();
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