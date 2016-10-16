#include "breakout.hpp"

namespace breakout {
    
    Breakout game_breakout;
    
    Breakout::~Breakout() {
        
    }
    
    void Breakout::loadData() {
        
    }
    
    void Breakout::draw() {
        
    }
    
    void Breakout::update() {

    	const unsigned char *keys = SDL_GetKeyboardState(NULL);

    	if(keys[SDL_SCANCODE_LEFT]) {

    	}
    	else if(keys[SDL_SCANCODE_RIGHT]) {

    	}
    	else if(keys[SDL_SCANCODE_UP]) {

    	}
    	else if(keys[SDL_SCANCODE_DOWN]) {

    	}

    }
    
    void Breakout::keydown(int key) {
        
    }
    
    void Breakout::keyup(int key) {
        
    }

    Brick::Brick() : brick_type(0), visible(false) {

    }

    void Brick::setVisible(const bool &b) {

    }
    bool Brick::isVisible() const {
    	return visible;
    }

    int Brick::getType() const {
    	return brick_type;
    }

    void Brick::setType(const int &b) {
    	brick_type = b;
    }

    Paddle::Paddle(int cx, int cy, int cw, int ch) : x(cx), y(cy), w(cw), h(ch) {

    }

    void Paddle::move(Direction dir) {
    	switch(dir) {
    	case Direction::LEFT:
    		if(x > 0) x -= 4;
    		break;
    	case Direction::RIGHT:
    		if(x < 1280-w) x += 4;
    		break;
    	case Direction::UP:
    		if(y > 360) y -= 4;
    		break;
    	case Direction::DOWN:
    		if(y < 720-h) y += 4;
    		break;
    	}
    }


}
