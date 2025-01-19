#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;	// window width
const int SCREEN_HEIGHT = 480;	// window height

class GameState {
	public:
		virtual void handleEvents( SDL_Event& e ) = 0;
		virtual void update() = 0;
		virtual void render( SDL_Surface* surface ) = 0;
		virtual ~GameState() {}
};

class PlayState : public GameState {
	private: Uint8 r, g, b;

	public: PlayState() : r(255), g(255), b(255) {}

	void handleEvents( SDL_Event& e ) override {
		if( e.type == SDL_KEYDOWN ) {	// Checking whether a key is pressed
			switch ( e.key.keysym.sym ) {
			case SDLK_w: r = 255; g = 255; b = 255; break;
			case SDLK_r: r = 255; g = 0;   b = 0;   break;
			case SDLK_g: r = 0;	  g = 255; b = 0;   break;
			case SDLK_b: r = 0;	  g = 0;   b = 255; break;
			
			default: break;
			}
		}
    }

    void update() override {}

    void render( SDL_Surface* surface ) override {
		Uint32 color = SDL_MapRGB( surface->format, r, g, b );	// set color
		SDL_FillRect( surface, NULL, color );
    }
};

int main( int argc, char* args[] ) {
	SDL_Window* window = NULL;	//The window we'll be rendering to
	SDL_Surface* screenSurface = NULL;	//The surface contained by the window

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {	//Initialize SDL
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	else {	//Create window
		window = SDL_CreateWindow( "SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			SDL_Quit();
			return -1;
		}
		else {
			screenSurface = SDL_GetWindowSurface( window );	//Get window surface

			GameState* currentState = new PlayState();

            SDL_Event e;	// Event
			bool quit = false;	// flag for window stay displayed
			Uint32 frameStart;
			const int FPS = 60;
			const int frameDelay = 1000 / FPS;

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
				currentState->render( screenSurface );
				SDL_UpdateWindowSurface( window );

				// 4. FPS manager
				Uint32 frameTime = SDL_GetTicks() - frameStart;
				if ( frameDelay > frameTime ) {
					SDL_Delay( frameDelay - frameTime );
				}
			}
			delete currentState;
		}
	}

	SDL_DestroyWindow( window );	//Destroy window
	SDL_Quit();	//Quit SDL subsystems

	return 0;
}