#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>

#include "Graphics/WindowManager.h"
#include "Game/GameState.h"
#include "Game/GameManager.h"

int main( int /*argc*/, char** /*args[]*/ ) {
	WindowManager windowManager;
	
	if( !windowManager.init() ) {
		std::cout << "Failed to initialize WindowManager" << std::endl;
		return -1;
	}
	else {
		std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>( &windowManager );
		gameManager->setNextState( std::make_unique<PlayState>( &windowManager ) );
		gameManager->changeState();

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
				gameManager->getCurrentState()->handleEvents( e );
			}

			// 2. Logic update
			gameManager->getCurrentState()->update();

			// 3. Rendering
			gameManager->getCurrentState()->render();
			SDL_RenderPresent( windowManager.getRenderer() );

			// 4. FPS manager
			Uint32 frameTime = SDL_GetTicks() - frameStart;
			if ( FRAME_DELAY > frameTime ) {
				SDL_Delay( FRAME_DELAY - frameTime );
			}
		}
	}
	return 0;
}