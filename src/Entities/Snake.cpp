#include "Snake.h"

Head::Head() {}

void Head::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderFillRect(renderer, &rect);
}

void Head::updatePosition() {}

void Head::move() {}

void Head::setPosition( int x, int y, int border ) {
    rect.x = x + border;
    rect.y = y + border;
}

void Head::setSize( int w, int h ) {
    rect.w = w;
    rect.h = h;
}

Head::~Head() {}