#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <SDL2/SDL.h>

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

#endif
