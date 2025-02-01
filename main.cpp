#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>

class WindowManager {
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		const int W_POS_X = SDL_WINDOWPOS_UNDEFINED;
		const int W_POS_Y = SDL_WINDOWPOS_UNDEFINED;
		int SCREEN_WIDTH;
		int SCREEN_HEIGHT;
		int D_INDEX = -1;
		std::string title;
		Uint8 r = 0, g = 0, b = 0, a = 255;
		const Uint32 R_FLAGS = SDL_RENDERER_ACCELERATED;
		const Uint32 W_FLAGS = SDL_WINDOW_SHOWN;
	
	public:
	// constructor
	WindowManager(const std::string& title = "SDL Window", int width = 640, int height = 480)
	: title(title), SCREEN_WIDTH(width), SCREEN_HEIGHT(height) {}

	bool init() {
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
			printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
			return false;
		}

		window = SDL_CreateWindow( title.c_str(), W_POS_X, W_POS_Y, SCREEN_WIDTH, SCREEN_HEIGHT, W_FLAGS );
		if( window == nullptr ) { 
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			cleanup();
			return false;
		}

		renderer = SDL_CreateRenderer( window, D_INDEX, R_FLAGS );
		if( renderer == nullptr ) {
			printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
			return false;
		}

		return true;
	}

	// get fields 
	SDL_Window* getWindow() const { return window; }
	SDL_Renderer* getRenderer() const { return renderer; }
	int getWidth() const { return SCREEN_WIDTH; }
	int getHeight() const { return SCREEN_HEIGHT; }

	void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255) {
		r = red; g = green; b = blue; a = alpha;
	}

	void clearWindow() {
		SDL_SetRenderDrawColor( renderer, r, g, b, a );	// set color
		SDL_RenderClear( renderer );
    }

	// clean up all for close program
	void cleanup() {
		if( renderer != nullptr ) {
			SDL_DestroyRenderer( renderer );
			renderer = nullptr;
		}

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