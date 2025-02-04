#include "Player.h"

Player::Player() {}

void Player::draw( SDL_Renderer* renderer ) {
    SDL_SetRenderDrawColor( renderer, r, g, b, a );
    SDL_RenderFillRect( renderer, &rect );
}

void Player::move_right() {
    x++;
    rect = { x, y, w, h };
    std::cout << "Position X: " << x << std::endl;
}

Player::~Player() {}