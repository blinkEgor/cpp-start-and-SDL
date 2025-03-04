#include "StartMenuState.h"

StartMenuState::StartMenuState( WindowManager* windowManager, GameManager* gameManager ) : 
    windowManager( windowManager ),
    gameManager( gameManager ),
    startMenu( windowManager->getWidth(), windowManager->getHeight() )
{}

// Отлов пользовательского взаимодействия
// - Проверяем был ли клик мышкой
// - - Отлавливаем позицию клика
// - - И передам позицию функции для смены флага нажатия на кнопку
void StartMenuState::handleEvents( SDL_Event& e ) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x, y = e.button.y;
        startMenu.setClick( x, y );
    }
}

// Обновление логики StartMenuState
// - Проверяем флаг нажатия на кнопку старта игры
// - - Переход в PlayState
void StartMenuState::update() {
    if ( startMenu.getIsClicked() ) {
        gameManager->setNextState( std::make_unique<PlayState>( windowManager, gameManager ));
        gameManager->changeState();
    }
}

// Отрисовка объектов в StartMenuState
// - Очистка окна чёрным цветом
// - Рисуем все элементы стартового меню
void StartMenuState::render() {
    windowManager->clearWindow();
    startMenu.draw( windowManager->getRenderer() );
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