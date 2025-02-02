#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>
#include "WindowManager.h"

class GameState {
	public:
		virtual void handleEvents( SDL_Event& e ) = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual ~GameState() {}
};

class PlayState : public GameState {
	private:
		WindowManager* windowManager;
	public: 
	PlayState(WindowManager* windowManager) : windowManager(windowManager) {}

	void handleEvents( SDL_Event& e ) override {
		if( e.type == SDL_KEYDOWN ) {	// Checking whether a key is pressed
			// switch ( e.key.keysym.sym ) {
			// case SDLK_c: windowManager->setColor( 0, 0, 0 ); break;
			// case SDLK_r: windowManager->setColor( 255, 0, 0 ); break;
			// case SDLK_g: windowManager->setColor( 0, 255, 0 ); break;
			// case SDLK_b: windowManager->setColor( 0, 0, 255 ); break;

			// Эта механика была тестовая, для понимания работы заливки окна
			// и сейча она не нужна, поэтому метод тоже удалил. 
			// Оставил в комментарии для образка, как использовать ивенты.
			
			// default: break;
			// }
		}
    }

    void update() override {}

    void render() override {
		windowManager->clearWindow();
    }
};

int main( int argc, char* args[] ) {
	WindowManager windowManager;
	
	if( !windowManager.init() ) {
		std::cout << "Failed to initialize WindowManager" << std::endl;
		return -1;
	}
	else {
		std::unique_ptr<GameState> currentState = std::make_unique<PlayState>(&windowManager);

		SDL_Event e;	// Event
		bool quit = false;	// flag for window stay displayed
		Uint32 frameStart;
		const int FPS = 60;
		const int FRAME_DELAY = 1000 / FPS;

		while( quit == false ) {	// GameLoop
			frameStart = SDL_GetTicks();
			
			// 1. Event handling
			while( SDL_PollEvent( &e ) ) {	// check close window
				if( e.type == SDL_QUIT ) quit = true;
				currentState->handleEvents( e );
			}

			// 2. Logic update
			currentState->update();

			// 3. Rendering
			SDL_RenderPresent( windowManager.getRenderer() );
			currentState->render();

			// 4. FPS manager
			Uint32 frameTime = SDL_GetTicks() - frameStart;
			if ( FRAME_DELAY > frameTime ) {
				SDL_Delay( FRAME_DELAY - frameTime );
			}
		}
	}

	windowManager.cleanup();

	return 0;
}