#ifdef _WIN32
	#define SDL_MAIN_HANDLED

	#include <SDL.h>
	#include <SDL_ttf.h>
	#include <SDL_image.h>
#else
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
	#include <SDL2/SDL_image.h>
#endif

#include <fstream>
#include <iostream>
#include <map>
#include <stack>
using namespace std;

#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "json.hpp"
using json = nlohmann::json;

#include "Border.h"
#include "Color.h"
#include "FontResource.h"
#include "GameState.h"
#include "i18n.h"
#include "Rectangle.h"
#include "renderHelpers.h"
#include "Resource.h"
#include "ResourceFactory.h"

#define PATH_SETTINGS "settings.json"

// TODO: Need a better logging system.

class SampleGameState: public GameState {
	private:
		bool _isDragging;
		bool _isHovering;
		Border* _border;
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
	: _isDragging(false), _isHovering(false) {
	ResourceFactory::get()->load<FontResource>("fontMain", "./assets/fonts/fontMain.json");

	_border = new Border(200, 200, 64, 32);
}

SampleGameState::~SampleGameState() {
	if (_border != nullptr) {
		delete _border;
		_border = nullptr;
	}

	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}
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
	setRenderColor(renderer, Color(0, 0, 0));
	SDL_RenderClear(renderer);

	if (_isDragging) {
		_border->setBorderColor(0, 255, 0);
	} else if (_isHovering) {
		_border->setBorderColor(255, 255, 0);
	} else {
		_border->setBorderColor(255, 0, 0);
	}
	_border->render(renderer);

	renderText(renderer, ResourceFactory::get()->get<FontResource>("fontMain")->getValue(), _("Hello, world!"), 320, 240, Color(255, 200, 0));

	Rectangle imageRect(100, 100, 16, 16);
	setTextureColor(_texture, Color(255, 0, 255));
	SDL_RenderCopy(renderer, _texture, NULL, &imageRect);

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
	_isHovering = _border->getRect()->contains(motion.x, motion.y);
	if (_isDragging) {
		_border->getRect()->moveBy(motion.xrel, motion.yrel);
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

#ifdef _WIN32
#else
	/* Setting the i18n environment */
	setlocale(LC_ALL, "");
	bindtextdomain("logi-game", "./locale");
	textdomain("logi-game");
#endif

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cerr << _("Unable to initialize SDL: ") << SDL_GetError() << endl;
		return false;
	}

	int width = settings["graphics"]["width"].get<int>();
	int height = settings["graphics"]["height"].get<int>();
	if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) != 0) {
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
	ResourceFactory::shutdown();

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