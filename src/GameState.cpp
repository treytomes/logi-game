#include "GameState.h"

GameState::GameState()
	: _isLeaving(false) {
}

void GameState::leave() {
	_isLeaving = true;
}

bool GameState::isLeaving() {
	return _isLeaving;
}
