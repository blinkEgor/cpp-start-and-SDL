#include <SDL2/SDL.h>
#include <iostream>

class Player {
private:
    Uint8 r = 255, g = 255, b = 255, a = 255; // color 
    int x = 64, y = 64, w = 32, h = 32; // position and size 
    SDL_Rect rect = { x, y, w, h };
public:
    Player();
    void draw( SDL_Renderer* renderer );
    ~Player();
};
