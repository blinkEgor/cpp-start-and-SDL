#include "PlayState.h"

PlayState::PlayState( WindowManager* windowManager, GameManager* gameManager ) : 
    windowManager( windowManager ),
    gameManager( gameManager ),
    grid(),
    snake( &grid, &food, 5, 5 ),
    food( &grid ),
    restartButton( windowManager->getWidth(), windowManager->getHeight() )
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
    if ( !snake.getIsAlive() ) {
        if ( e.type == SDL_MOUSEBUTTONDOWN ) {
            int x = e.button.x, y = e.button.y;
            restartButton.setClick( x, y );
        }
    }
}

// Обновляет логику игры:
// - Если змейка жива: двигается, растёт, проверяет столкновение.
// - Если мертва: логируем сообщение только один раз.
void PlayState::update() {
    static bool logged_death = false;
    if ( snake.getIsAlive() ) {
        snake.checkCollision();
        snake.move();
        snake.grow();
        logged_death = false;
    } else {
        if ( !logged_death ) {
            logError( "Snake is died", LogLevel::INFO );
            logged_death = true;
        }
        if ( restartButton.getIsClicked() ) {
            gameManager->setNextState( std::make_unique<StartMenuState>( windowManager, gameManager ));
            gameManager->changeState();
        }
    }
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
    if ( !snake.getIsAlive() ) {
        restartButton.draw( windowManager->getRenderer() );
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
    logError( "The size of your snake was: " + std::to_string( snake.getNumberOfSegments() ), LogLevel::INFO );
    logError( "Exiting PlayState", LogLevel::INFO );
}