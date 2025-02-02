#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>

#include "WindowManager.h"
#include "GameState.h"

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