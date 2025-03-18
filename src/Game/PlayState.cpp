#include "PlayState.h"

PlayState::PlayState( WindowManager* window_manager, GameState::StateChangeCallback callback ) : 
    window_manager( window_manager ),
    m_grid(),
    m_food( &m_grid ),
    m_snake( &m_grid, &m_food, 5, 5 ),
    m_restart_button( window_manager->get_screen_width(), window_manager->get_screen_height() )
{
    set_state_change_callback( callback ); // Устанавливаем коллбэк
}

// Отлов пользовательского взаимодействия
// - Отлавливаем пользовательское событие нажатия на клавиши клавиатуры
// - - Отлов нажатия на определенный клавиши
// - - - Нажатие на W - направление вверх
// - - - Нажатие на A - направление влево
// - - - Нажатие на S - направление вниз
// - - - Нажатие на D - направление вправо
void PlayState::handle_events( SDL_Event& e ) {
    if ( e.type == SDL_KEYDOWN ) {
        switch ( e.key.keysym.sym ) {
            case SDLK_w: m_snake.set_direction( 0, -1 ); break;
            case SDLK_s: m_snake.set_direction( 0, 1 );  break;
            case SDLK_a: m_snake.set_direction( -1, 0 ); break;
            case SDLK_d: m_snake.set_direction( 1, 0 );  break;
        }
    }
    if ( !m_snake.get_is_alive() ) {
        if ( e.type == SDL_MOUSEBUTTONDOWN ) {
            int x = e.button.x, y = e.button.y;
            m_restart_button.set_click( x, y );
        }
    }
}

// Обновляет логику игры:
// - Если змейка жива: двигается, растёт, проверяет столкновение.
// - Если мертва: логируем сообщение только один раз и
// используем коллбэк для смены состояния
void PlayState::update() {
    static bool logged_death = false;
    if ( m_snake.get_is_alive() ) {
        m_snake.check_collision();
        m_snake.move();
        m_snake.grow();
        logged_death = false;
    } else {
        if ( !logged_death ) {
            logError( "Snake is died", LogLevel::INFO );
            logged_death = true;
        }
        if ( m_restart_button.get_is_clicked() ) {
            if ( state_change_callback ) {
                state_change_callback( std::make_unique<StartMenuState>( window_manager, state_change_callback ) );
            }
        }
    }
}

// Отрисовка объектов в PlayState
// - Кэшируем рендерер, для читаемости и микро-оптимизации
// - Очистка окна чёрным цветом
// - Отрисовка сетки
// - Отрисовка еды
// - Отрисовка змейки
void PlayState::render( SDL_Renderer* renderer ) {
    window_manager->clear_window();
    m_grid.draw_grid( renderer );
    m_food.draw( renderer );
    m_snake.draw( renderer );
    if ( !m_snake.get_is_alive() ) {
        m_restart_button.draw( renderer );
    }
}

// Вход в игровое состояние PlayState
// - Логируем сообщение о входе в игровое состояние
void PlayState::enter() {
    logError( "Entering PlayState", LogLevel::INFO );
    logError( "Starting size of the snake: 1", LogLevel::INFO );
}

// Выход из игрового состояния PlayState
// - Логируем сообщение о выходе из игрового состояния
void PlayState::exit() {
    logError( "The size of your snake was: " + std::to_string( m_snake.get_number_of_segments() ), LogLevel::INFO );
    logError( "Exiting PlayState", LogLevel::INFO );
}