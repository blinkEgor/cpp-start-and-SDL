#pragma once

class BodyParts {
    virtual void draw() = 0;
    virtual void play() = 0;
    virtual void move() = 0;
	virtual ~BodyParts() {}
};

class Head : public BodyParts {
private:
    
public:

};

class Body : public BodyParts {
private:

public:

};

class Snake {
private:

public:

};