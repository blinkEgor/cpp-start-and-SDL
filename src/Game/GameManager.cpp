#include "GameManager.h"

GameManager::GameManager( WindowManager* window_manager ) : 
    window_manager( window_manager )
{ 
    // Создаю коллбэк для смены состояния (лямбда-функция)
    auto set_next_state_callback = [ this ]( std::unique_ptr<GameState> new_state ) {
        set_next_state( std::move( new_state ) );
    };
    
    // Ставлю состояние игры по умолчанию
    set_next_state( std::make_unique<StartMenuState>( window_manager, set_next_state_callback ) );
    change_state();
}

// Игровой цикл в котором есть переменны для управления кадрами, закрытием окна, объявление ивентов
void GameManager::game_loop() {
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
                get_current_state()->exit();
            }
            get_current_state()->handle_events( e );
        }

        // 2. Logic update
        get_current_state()->update();

        // 3. Rendering
        window_manager->clear_window( Palette::CLEAR_WINDOW );
        get_current_state()->render( window_manager->get_renderer() );
        SDL_RenderPresent( window_manager->get_renderer() );

        // 4. FPS manager
        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if ( FRAME_DELAY > frame_time ) {
            SDL_Delay( FRAME_DELAY - frame_time );
        }

        // 5. Change GameState if needs
        change_state();
    }
}

// Назначаем следующее состояние игры
void GameManager::set_next_state( std::unique_ptr<GameState> new_next_state ) {
    m_next_state = std::move( new_next_state );
}

// Меняем состояние игры
// - Завершаем текущее состояние
// - Инициализируем новое состояние
void GameManager::change_state() {
    if ( m_next_state ) {
        if ( m_current_state ) {
            m_current_state->exit();
        }
        m_current_state = std::move( m_next_state );
        m_current_state->enter();
    }
}

// Получаем текущее состояние игры
GameState* GameManager::get_current_state() const { return m_current_state.get(); }
