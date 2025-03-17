#include "GameManager.h"

GameManager::GameManager( WindowManager* windowManager ) : 
    windowManager( windowManager )
{ 
    // Создаем коллбэк для смены состояния
    auto callback = [ this ]( std::unique_ptr<GameState> newState ) {
        setNextState( std::move( newState ) );
    };
    
    // Ставим состояние игры по умолчанию
    setNextState( std::make_unique<StartMenuState>( windowManager, callback ) );
    changeState();
}

// Игровой цикл в котором есть переменны для управления кадрами, закрытием окна, объявление ивентов
void GameManager::gameLoop() {
    SDL_Event e;	// Event
    bool quit = false;	// flag for window stay displayed
    Uint32 frame_start;
    const int ONE_SEC = 1000;
    const int FPS = 60;
    const int FRAME_DELAY = ONE_SEC / FPS;

    while( quit == false ) {
        frame_start = SDL_GetTicks();
        
        // 1. Event handling
        while( SDL_PollEvent( &e ) ) {
            if( e.type == SDL_QUIT ) { // check close window
                quit = true;
                getCurrentState()->exit();
            }
            getCurrentState()->handleEvents( e );
        }

        // 2. Logic update
        getCurrentState()->update();

        // 3. Rendering
        getCurrentState()->render( windowManager->getRenderer() );
        SDL_RenderPresent( windowManager->getRenderer() );

        // 4. FPS manager
        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if ( FRAME_DELAY > frame_time ) {
            SDL_Delay( FRAME_DELAY - frame_time );
        }

        // 5. Change GameState if needs
        changeState();
    }
}

// Назначаем следующее состояние игры
void GameManager::setNextState( std::unique_ptr<GameState> newState ) {
    nextState = std::move( newState );
}

// Меняем состояние игры
// - Завершаем текущее состояние
// - Инициализируем новое состояние
void GameManager::changeState() {
    if ( nextState ) {
        if ( currentState ) {
            currentState->exit();
        }
        currentState = std::move( nextState );
        currentState->enter();
        nextState = nullptr;
    }
}

// Получаем текущее состояние игры
GameState* GameManager::getCurrentState() const { return currentState.get(); }
