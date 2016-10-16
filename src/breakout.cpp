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
}
