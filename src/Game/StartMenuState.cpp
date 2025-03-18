#include "StartMenuState.h"

StartMenuState::StartMenuState( WindowManager* window_manager, GameState::StateChangeCallback callback ) : 
    window_manager( window_manager ),
    m_start_menu( window_manager->get_screen_width(), window_manager->get_screen_height() )
{
    set_state_change_callback( callback );
}

// Отлов пользовательского взаимодействия
// - Проверяем был ли клик мышкой
// - - Отлавливаем позицию клика
// - - И передам позицию функции для смены флага нажатия на кнопку
void StartMenuState::handle_events( SDL_Event& e ) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x, y = e.button.y;
        m_start_menu.set_click( x, y );
    }
}

// Обновление логики StartMenuState
// - Проверяем флаг нажатия на кнопку старта игры
// - - Используем коллбэк для смены состояния
void StartMenuState::update() {
    if ( m_start_menu.get_is_clicked() ) {
        if ( state_change_callback ) {
            state_change_callback( std::make_unique<PlayState>( window_manager, state_change_callback ) );
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