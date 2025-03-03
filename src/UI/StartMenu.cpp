#include "StartMenu.h"

StartMenu::StartMenu() : 
    is_clicked( false )
{
    button_rect = { 100, 100, 200, 50 };
}

void StartMenu::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, 0, 255, 0, 255 ); // Зелёный цвет
    SDL_RenderFillRect( renderer, &button_rect );
}

void StartMenu::setClick( int x, int y ) {
    if ( x >= button_rect.x && x <= button_rect.x + button_rect.w /* Проверка по ширине */ && 
         y >= button_rect.y && y <= button_rect.y + button_rect.h /* Проверка по высоте */ ) {
        is_clicked = true;
    }
}

bool StartMenu::getIsClicked() const { return is_clicked; }