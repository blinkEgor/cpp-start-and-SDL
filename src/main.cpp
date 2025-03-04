#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>

#include "Graphics/WindowManager.h"
#include "Game/GameState.h"
#include "Game/GameManager.h"

int main( int /*argc*/, char** /*args[]*/ ) {
	WindowManager windowManager( "Snake", 32*24+32, 32*16+32 );
	
	if( !windowManager.init() ) {
		std::cout << "Failed to initialize WindowManager" << std::endl;
		return -1;
	}
	else {
		GameManager gameManager( &windowManager );
		// gameManager.setNextState( std::make_unique<PlayState>( &windowManager ) );
		gameManager.setNextState( std::make_unique<StartMenuState>( &windowManager ) );
		gameManager.changeState();

		SDL_Event e;	// Event
		bool quit = false;	// flag for window stay displayed
		Uint32 frame_start;
		const int FPS = 60;
		const int FRAME_DELAY = 1000 / FPS;

		while( quit == false ) {	// GameLoop
			frame_start = SDL_GetTicks();
			
			// 1. Event handling
			while( SDL_PollEvent( &e ) ) {	// check close window
				if( e.type == SDL_QUIT ) quit = true;
				gameManager.getCurrentState()->handleEvents( e );
			}

			// 2. Logic update
			gameManager.getCurrentState()->update();

			// 3. Rendering
			gameManager.getCurrentState()->render();
			SDL_RenderPresent( windowManager.getRenderer() );

			// 4. FPS manager
			Uint32 frame_time = SDL_GetTicks() - frame_start;
			if ( FRAME_DELAY > frame_time ) {
				SDL_Delay( FRAME_DELAY - frame_time );
			}
		}
	}
	return 0;
}