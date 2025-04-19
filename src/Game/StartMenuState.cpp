#include "StartMenuState.h"

StartMenuState::StartMenuState( WindowManager* window_manager, GameState::NextStateCallback set_next_state_callback ) : 
    window_manager( window_manager ), 
    m_start_menu( { window_manager->get_screen_width(), window_manager->get_screen_height() } )
{
    this->set_next_state_callback( set_next_state_callback );
}

// Отлов пользовательского взаимодействия
// - Проверяем был ли клик мышкой
// - - Отлавливаем позицию клика
// - - И передам позицию функции для смены флага нажатия на кнопку
void StartMenuState::handle_events( SDL_Event& e ) {
    m_start_menu.handle_input( e );
    // if (e.type == SDL_MOUSEBUTTONDOWN) {
    //     int x = e.button.x, y = e.button.y;
    //     m_start_menu.set_click( x, y );
    // }
}

// Обновление логики StartMenuState
// - Проверяем флаг нажатия на кнопку старта игры
// - - Используем коллбэк для смены состояния
void StartMenuState::update() {
    if ( false ) {
        if ( m_set_next_state_callback ) {
            m_set_next_state_callback( std::make_unique<PlayState>( window_manager, m_set_next_state_callback ) );
        }
    }
}

// Отрисовка объектов в StartMenuState
// - Очистка окна чёрным цветом
// - Рисуем все элементы стартового меню
void StartMenuState::render( SDL_Renderer* renderer ) {
    window_manager->clear_window();
    m_start_menu.draw( renderer );
}

// Вход в игровое состояние StartMenuState
// - Логируем сообщение о входе в игровое состояние
void StartMenuState::enter() {
    logError( "Entering StartMenuState", LogLevel::INFO );
}

// Выход из игрового состояния StartMenuState
// - Логируем сообщение о выходе из игрового состояния
void StartMenuState::exit() {
    logError( "Exiting StartMenuState", LogLevel::INFO );
}