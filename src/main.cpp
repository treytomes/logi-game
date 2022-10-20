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
#include "Color.h"

#define _(STRING) gettext(STRING)

#define PATH_SETTINGS "settings.json"

inline void setRenderColor(SDL_Renderer* renderer, Color color) {
	if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) == 0) {
		cerr << _("Unable to set render color: ") << SDL_GetError() << endl;
	}
}

inline void setTextureColor(SDL_Texture* texture, Color color) {
	if (SDL_SetTextureColorMod(texture, color.r, color.g, color.b) != 0) {
		cerr << _("Unable to set texture color: ") << SDL_GetError() << endl;
	}
}

class Border {
	private:
		Color _borderColor;
		Color _backgroundColor;
		Rectangle* _rect;

	public:
		Border(Rectangle rect);
		Border(int x, int y, int width, int height);
		~Border();
		void render(SDL_Renderer* renderer);

		inline Rectangle* getRect() { return _rect; }
		inline Color getBorderColor() { return _borderColor; }
		inline void setBorderColor(Color c) { _borderColor = c; }
		void setBorderColor(int r, int g, int b, int a = 255);
		inline Color getBackgroundColor() { return _backgroundColor; }
		inline void setBackgroundColor(Color c) { _backgroundColor = c; }
		void setBackgroundColor(int r, int g, int b, int a = 255);
};

Border::Border(Rectangle rect)
	: _borderColor(255, 255, 255), _backgroundColor(255, 255, 255), _rect(new Rectangle(rect)) {
}

Border::Border(int x, int y, int width, int height)
	: Border(Rectangle(x, y, width, height)) {
}

Border::~Border() {
	if (_rect != nullptr) {
		delete _rect;
		_rect = nullptr;
	}
}

void Border::render(SDL_Renderer* renderer) {
	setRenderColor(renderer, _backgroundColor);
	SDL_RenderFillRect(renderer, _rect);

	setRenderColor(renderer, _borderColor);
	SDL_RenderDrawLine(renderer, _rect->getLeft(), _rect->getTop(), _rect->getLeft(), _rect->getBottom());
	SDL_RenderDrawLine(renderer, _rect->getRight(), _rect->getTop(), _rect->getRight(), _rect->getBottom());
	SDL_RenderDrawLine(renderer, _rect->getLeft(), _rect->getTop(), _rect->getRight(), _rect->getTop());
	SDL_RenderDrawLine(renderer, _rect->getLeft(), _rect->getBottom(), _rect->getRight(), _rect->getBottom());
}

void Border::setBorderColor(int r, int g, int b, int a) {
	_borderColor.r = r;
	_borderColor.g = g;
	_borderColor.b = b;
	_borderColor.a = a;
}

void Border::setBackgroundColor(int r, int g, int b, int a) {
	_backgroundColor.r = r;
	_backgroundColor.g = g;
	_backgroundColor.b = b;
	_backgroundColor.a = a;
}

class SampleGameState: public GameState {
	private:
		bool _isDragging;
		bool _isHovering;
		Border* _border;
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
	: _isDragging(false), _isHovering(false) {
	_font = TTF_OpenFont("./assets/fonts/UbuntuMono/UbuntuMono-Regular.ttf", 16);
	if (!_font) {
		cerr << _("Error loading font: ") << TTF_GetError() << endl;
	}

	_border = new Border(200, 200, 64, 32);
}

SampleGameState::~SampleGameState() {
	if (_border != nullptr) {
		delete _border;
		_border = nullptr;
	}

	if (_font != nullptr) {
		TTF_CloseFont(_font);
		_font = nullptr;
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

	Color textColor(255, 255, 255);

	SDL_Surface* textSurface = TTF_RenderText_Solid(_font, _("Hello, world!"), textColor);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

	Rectangle textRect(320 - (textSurface->w / 2.0f), 240, textSurface->w, textSurface->h);
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);

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