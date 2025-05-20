#include "StartState.h"

StartState::StartState( WindowManager* window_manager, GameState::NextStateCallback set_next_state_callback ) : 
    window_manager( window_manager ), 
    m_start_menu( 
        { window_manager->get_screen_width(), window_manager->get_screen_height() }, 
        window_manager->get_renderer(),
        { 
            { 32, window_manager->get_font( 32 ) },
            { 64, window_manager->get_font( 64 ) }
        }
    )
{
    this->set_next_state_callback( set_next_state_callback );
}

// Отлов пользовательского взаимодействия
// - Проверяем был ли клик мышкой
// - - Отлавливаем позицию клика
// - - И передам позицию функции для смены флага нажатия на кнопку
void StartState::handle_events( SDL_Event& e ) {
    m_start_menu.handle_input( e );
}

// Обновление логики StartState
// - Проверяем флаг нажатия на кнопку старта игры
// - - Используем коллбэк для смены состояния
void StartState::update() {
    if ( m_start_menu.is_active_button() ) {
        if ( m_set_next_state_callback ) {
            m_set_next_state_callback( std::make_unique<PlayState>( window_manager, m_set_next_state_callback ) );
        }
    }
}

// Отрисовка объектов в StartState
// - Очистка окна чёрным цветом
// - Рисуем все элементы стартового меню
void StartState::render( SDL_Renderer* renderer ) {
    m_start_menu.draw( renderer );
}

// Вход в игровое состояние StartState
// - Логируем сообщение о входе в игровое состояние
void StartState::enter() {
    logError( "Entering StartState", LogLevel::INFO );
}

// Выход из игрового состояния StartState
// - Логируем сообщение о выходе из игрового состояния
void StartState::exit() {
    logError( "Exiting StartState", LogLevel::INFO );
}