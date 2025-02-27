#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "../Game/Grid.h"

class Snake {
public:
    virtual void draw( SDL_Renderer* renderer ) = 0;
    virtual void updatePosition() = 0;
    virtual void move() = 0;
	virtual ~Snake() {}
};

class Head : public Snake {
private:
    Uint8 r = 255, g = 255, b = 255, a = 255;
    SDL_Rect rect = { 16, 16, 32, 32 };
    
public:
    Head();
    void draw( SDL_Renderer* renderer );
    void updatePosition();
    void move();
    void setPosition( int x, int y, int border );
    void setSize( int w, int h );
    ~Head();
};

class Body : public Snake {
private:

public:

};