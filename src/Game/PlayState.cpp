#include "PlayState.h"

PlayState::PlayState( WindowManager* window_manager, GameState::NextStateCallback set_next_state_callback ) : 
    window_manager( window_manager ),
    m_grid(),
    m_snake( { 5, 5 } ),
    m_food( { 5, 15 } ), 
    m_restart_menu( 
        { window_manager->get_screen_width(), window_manager->get_screen_height() }, 
        window_manager->get_renderer(),
        {
            { 32, window_manager->get_font( 32 ) }
        }
    )
{
    #include <ctime> // Оно вызвано вместе с логами, но пусть наглядно будет тут, компилятор проигнорирует это
    srand( time( 0 ) ); // Устанавливаем место откуда брать псевдослучайное значение
    this->set_next_state_callback( set_next_state_callback ); // Устанавливаем коллбэк
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
            case SDLK_w:
            case SDLK_UP: m_snake.set_direction( { -1, 0 } ); break;
            case SDLK_s:
            case SDLK_DOWN: m_snake.set_direction( { 1, 0 } );  break;
            case SDLK_a:
            case SDLK_LEFT: m_snake.set_direction( { 0, -1 } ); break;
            case SDLK_d:
            case SDLK_RIGHT: m_snake.set_direction( { 0, 1 } );  break;
        }
    }
    if ( !m_snake.get_is_alive() ) {
        m_restart_menu.handle_input( e );
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
        if ( !is_equal_pair( m_snake.get_snake_direction(), { 0, 0 } ) ) {
            m_snake.move( m_grid.get_grid_field() );
        }
        if ( m_snake.grow( m_food.get_food_position() ) ) {
            m_food.respawn_food( m_grid.get_grid_field(), m_snake.get_snake_segments() );
        }
        logged_death = false;
    } else {
        if ( !logged_death ) {
            logError( "Snake is died", LogLevel::INFO );
            logged_death = true;
            // Обновляем значение счта на фактическое
            m_restart_menu.update( window_manager->get_renderer(), window_manager->get_font( 32 ), m_snake.get_number_of_segments() );

        }
        if ( m_restart_menu.is_active_button() ) {
            if ( m_set_next_state_callback ) {
                m_set_next_state_callback( std::make_unique<StartMenuState>( window_manager, m_set_next_state_callback ) );
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
    m_grid.draw_grid( renderer );
    m_food.draw( renderer, m_grid.get_cell_size(), m_grid.get_grid_border() );
    m_snake.draw( renderer, m_grid.get_cell_size(), m_grid.get_grid_border() );
    if ( !m_snake.get_is_alive() ) {
        m_restart_menu.draw( renderer );
    }
}

// Вход в игровое состояние PlayState
// - Логируем сообщение о входе в игровое состояние
void PlayState::enter() {
    logError( "Entering PlayState", LogLevel::INFO );
    logError( "Starting size of the snake: " + std::to_string( m_snake.get_number_of_segments() ), LogLevel::INFO );
}

// Выход из игрового состояния PlayState
// - Логируем сообщение о выходе из игрового состояния
void PlayState::exit() {
    logError( "The size of your snake was: " + std::to_string( m_snake.get_number_of_segments() ), LogLevel::INFO );
    logError( "Exiting PlayState", LogLevel::INFO );
}