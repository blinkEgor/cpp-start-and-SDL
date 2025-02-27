#pragma once
#include <iostream>
#include <SDL2/SDL.h>

class BodyParts {
public:
    virtual void draw( SDL_Renderer* renderer ) = 0;
    virtual void update_position() = 0;
    virtual void move() = 0;
	virtual ~BodyParts() {}
};

class Head : public BodyParts {
private:
    Uint8 r = 255, g = 255, b = 255, a = 255;
    SDL_Rect rect = { 16, 16, 32, 32 };
    
public:
    Head();
    void draw( SDL_Renderer* renderer );
    void update_position();
    void move();
};

class Body : public BodyParts {
private:

public:

};

class Snake {
private:

public:

};