#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <SDL2/SDL.h>

class GameState {
	private:
		bool _isLeaving;

	protected:

	public:
		GameState();
		virtual ~GameState();
		
		void pollEvents();
		virtual bool onKeyDown(SDL_KeyboardEvent key);
		virtual bool onKeyUp(SDL_KeyboardEvent key);
		virtual bool onMouseMotion(SDL_MouseMotionEvent motion);
		virtual bool onMouseButtonDown(SDL_MouseButtonEvent button);
		virtual bool onMouseButtonUp(SDL_MouseButtonEvent button);
		virtual bool onMouseWheel(SDL_MouseWheelEvent wheel);
		virtual bool onTextEditing(SDL_TextEditingEvent edit);
		virtual bool onTextInput(SDL_TextInputEvent text);

		virtual void enter(SDL_Renderer* renderer);
		virtual void updateFrame() = 0;
		virtual void renderFrame(SDL_Renderer* renderer) = 0;
		void leave();
		bool isLeaving();
};

#endif
