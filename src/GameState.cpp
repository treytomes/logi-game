#include "GameState.h"

GameState::GameState()
	: _isLeaving(false) {
}

GameState::~GameState() {
	
}

void GameState::leave() {
	_isLeaving = true;
}

bool GameState::isLeaving() {
	return _isLeaving;
}

void GameState::pollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		bool wasHandled = false;

		if (event.type == SDL_KEYDOWN) {
			wasHandled = onKeyDown(event.key);
		} else if (event.type == SDL_KEYUP) {
			wasHandled = onKeyUp(event.key);
		} else if (event.type == SDL_MOUSEMOTION) {
			wasHandled = onMouseMotion(event.motion);
		} else if (event.type == SDL_MOUSEBUTTONDOWN) {
			wasHandled = onMouseButtonDown(event.button);
		} else if (event.type == SDL_MOUSEBUTTONUP) {
			wasHandled = onMouseButtonUp(event.button);
		} else if (event.type == SDL_MOUSEWHEEL) {
			wasHandled = onMouseWheel(event.wheel);
		} else if (event.type == SDL_TEXTEDITING) {
			wasHandled = onTextEditing(event.edit);
		} else if (event.type == SDL_TEXTINPUT) {
			wasHandled = onTextInput(event.text);
		} else if (event.type == SDL_QUIT) {
			// The quit event is handled by the main event loop.
			wasHandled = false;
		}

		if (!wasHandled) {
			// If the event wasn't handled by this state, push it back onto the queue to be handled elsewhere.
			SDL_PushEvent(&event);
		}
	}
}

bool GameState::onKeyDown(SDL_KeyboardEvent key) {
	 return false;
}

bool GameState::onKeyUp(SDL_KeyboardEvent key) {
	return false;
}

bool GameState::onMouseMotion(SDL_MouseMotionEvent motion) {
	return false;
}

bool GameState::onMouseButtonDown(SDL_MouseButtonEvent button) {
	return false;
}

bool GameState::onMouseButtonUp(SDL_MouseButtonEvent button) {
	return false;
}

bool GameState::onMouseWheel(SDL_MouseWheelEvent wheel) {
	return false;
}

bool GameState::onTextEditing(SDL_TextEditingEvent edit) {
	return false;
}

bool GameState::onTextInput(SDL_TextInputEvent text) {
	return false;
}
