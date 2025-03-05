#include "PlayState.h"

PlayState::PlayState( WindowManager* windowManager, GameManager* gameManager ) : 
    windowManager( windowManager ),
    gameManager( gameManager ),
    grid(),
    snake( &grid, &food, 5, 5 ),
    food( &grid )
{}

// Отлов пользовательского взаимодействия
// - Отлавливаем пользовательское событие нажатия на клавиши клавиатуры
// - - Отлов нажатия на определенный клавиши
// - - - Нажатие на W - направление вверх
// - - - Нажатие на A - направление влево
// - - - Нажатие на S - направление вниз
// - - - Нажатие на D - направление вправо
void PlayState::handleEvents( SDL_Event& e ) {
    if ( e.type == SDL_KEYDOWN ) {
        switch ( e.key.keysym.sym ) {
            case SDLK_w: snake.setDirection( 0, -1 ); break;
            case SDLK_s: snake.setDirection( 0, 1 );  break;
            case SDLK_a: snake.setDirection( -1, 0 ); break;
            case SDLK_d: snake.setDirection( 1, 0 );  break;
        }
    }
}

// Обновление логики PlayState
// - Двидение змейки
// - Рост змейки
void PlayState::update() {
    snake.move();
    snake.grow();
}

// Отрисовка объектов в PlayState
// - Кэшируем рендерер, для читаемости и микро-оптимизации
// - Очистка окна чёрным цветом
// - Отрисовка сетки
// - Отрисовка еды
// - Отрисовка змейки
void PlayState::render() {
    SDL_Renderer* renderer = windowManager->getRenderer();
    windowManager->clearWindow();
    grid.drawGrid( renderer );
    food.draw( renderer );
    snake.draw( renderer );
}

// Вход в игровое состояние PlayState
// - Логируем сообщение о входе в игровое состояние
void PlayState::enter() {
    logError( "Entering PlayState", LogLevel::INFO );
}

// Выход из игрового состояния PlayState
// - Логируем сообщение о выходе из игрового состояния
void PlayState::exit() {
    logError( "Exiting PlayState", LogLevel::INFO );
}