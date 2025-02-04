#include "Player.h"

Player::Player() {}

void Player::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderFillRect( renderer, &rect );
}

Player::~Player() {}