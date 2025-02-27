#include "Snake.h"

Head::Head() {}

void Head::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderFillRect(renderer, &rect);
}

void Head::update_position() {}

void Head::move() {}