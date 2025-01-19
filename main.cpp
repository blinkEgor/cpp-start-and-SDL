#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void changeWindowColor( SDL_Window* window, SDL_Surface* surface, Uint8 r, Uint8 g, Uint8 b ) {
	Uint32 color = SDL_MapRGB( surface->format, r, g, b );
	SDL_FillRect( surface, NULL, color);
	SDL_UpdateWindowSurface( window );
};

int main( int argc, char* args[] ) {
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else {
		//Create window
		window = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			changeWindowColor(window, screenSurface, 255, 255, 255);

            //Hack to get window to stay up like gameLoop
            SDL_Event e; bool quit = false; while( quit == false ){ 
				while( SDL_PollEvent( &e ) ){ 
					if( e.type == SDL_QUIT ) quit = true;
					// Checking whether a key is pressed
					if( e.type == SDL_KEYDOWN ) {
						switch (e.key.keysym.sym) {
						case SDLK_w: changeWindowColor(window, screenSurface, 255, 255, 255);
							break;
						case SDLK_r: changeWindowColor(window, screenSurface, 255, 0, 0);
							break;
						case SDLK_g: changeWindowColor(window, screenSurface, 0, 255, 0);
							break;
						case SDLK_b: changeWindowColor(window, screenSurface, 0, 0, 255);
							break;
						
						default:
							break;
						}
					}
				} 
			}
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}