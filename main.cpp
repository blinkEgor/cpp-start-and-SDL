#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>

class WindowManager {
	private:	// set default value
		SDL_Window* window = nullptr;
		SDL_Surface* screenSurface = nullptr;
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		std::string title;
		Uint8 r, g, b;
	
	public:
	// constructor
	WindowManager(const std::string& title = "SDL Window", int width = 640, int height = 480)
	: title(title), SCREEN_WIDTH(width), SCREEN_HEIGHT(height) {}

	bool init() {
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {	//Initialize SDL
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
			return false;
		}

		window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == nullptr ) { 
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			cleanup();
			return false;
		}

		screenSurface = SDL_GetWindowSurface( window );
		if( screenSurface == nullptr ) {
			printf( "Surface could not be created! SDL_Error: %s\n", SDL_GetError() );
			cleanup();
			return false;
		}

		return true;
	}

	// get fields 
	SDL_Window* getWindow() const { return window; }
	SDL_Surface* getSurface() const { return screenSurface; }
	int getWidth() const { return SCREEN_WIDTH; }
	int getHeight() const { return SCREEN_HEIGHT; }

	void setColor(Uint8 red, Uint8 green, Uint8 blue) {
        r = red; g = green; b = blue;
    }
	void clearWindow() {
        Uint32 color = SDL_MapRGB(screenSurface->format, r, g, b);
        SDL_FillRect(screenSurface, NULL, color);
    }

	// clean up all for close program
	void cleanup() {
		if( window != nullptr ) {
			SDL_DestroyWindow( window );
			window = nullptr;
		}
		SDL_Quit();
	}

	// destructor
	~WindowManager() { cleanup(); }
};

class GameState {
	public:
		virtual void handleEvents( SDL_Event& e ) = 0;
		virtual void update() = 0;
		virtual void render( SDL_Surface* surface ) = 0;
		virtual ~GameState() {}
};

class PlayState : public GameState {
	private:
		WindowManager* windowManager;
	public: 
	PlayState(WindowManager* windowManager) : windowManager(windowManager) {}

	void handleEvents( SDL_Event& e ) override {
		if( e.type == SDL_KEYDOWN ) {	// Checking whether a key is pressed
			switch ( e.key.keysym.sym ) {
			case SDLK_c: windowManager->setColor( 0, 0, 0 ); break;
			case SDLK_r: windowManager->setColor( 255, 0, 0 ); break;
			case SDLK_g: windowManager->setColor( 0, 255, 0 ); break;
			case SDLK_b: windowManager->setColor( 0, 0, 255 ); break;
			
			default: break;
			}
		}
    }

    void update() override {}

    void render( SDL_Surface* surface ) override {
		windowManager->clearWindow();
    }
};

int main( int argc, char* args[] ) {
	WindowManager* windowManager = new WindowManager();
	
	if( !windowManager->init() ) {
		std::cout << "Failed to initialize WindowManager" << std::endl;
		return -1;
	}
	else {
		GameState* currentState = new PlayState(windowManager);

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
			currentState->render( windowManager->getSurface() );
			SDL_UpdateWindowSurface( windowManager->getWindow() );

			// 4. FPS manager
			Uint32 frameTime = SDL_GetTicks() - frameStart;
			if ( frameDelay > frameTime ) {
				SDL_Delay( frameDelay - frameTime );
			}
		}
		delete currentState;
	
	}

	windowManager->cleanup();
	delete windowManager;

	return 0;
}