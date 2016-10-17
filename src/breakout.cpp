#include "breakout.hpp"

namespace breakout {
    
    Breakout game_breakout;
    
    Breakout::~Breakout() {
    }
    
    void Breakout::loadData() {
    	//SDL_SetColorKey(ball, SDL_TRUE, SDL_MapRGB(ball->format, 0, 0, 0));
    	the_game.init();
    }
    
    void Breakout::draw() {
        the_game.draw();

    }
    
    void Breakout::update() {
    	const unsigned char *keys = SDL_GetKeyboardState(NULL);

    	if(keys[SDL_SCANCODE_LEFT]) {
    		the_game.player.move(Direction::LEFT);
    	}

    	if(keys[SDL_SCANCODE_RIGHT]) {
    		the_game.player.move(Direction::RIGHT);
    	}

    	if(keys[SDL_SCANCODE_UP]) {
    		the_game.player.move(Direction::UP);
    	}

    	if(keys[SDL_SCANCODE_DOWN]) {
    		the_game.player.move(Direction::DOWN);
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
    		if(x > 0) x -= PADDLE_SPEED;
    		break;
    	case Direction::RIGHT:
    		if(x < 1280-w) x += PADDLE_SPEED;
    		break;
    	case Direction::UP:
    		if(y > 360) y -= PADDLE_SPEED;
    		break;
    	case Direction::DOWN:
    		if(y < 720-h) y += PADDLE_SPEED;
    		break;
    	default:
    		break;
    	}
    }

    void Paddle::setRect(SDL_Rect *rc) {
    	rc->x = x;
    	rc->y = y;
    	rc->w = w;
    	rc->h = h;
    }

    Ball::Ball() : x(0), y(0), w(0), h(0), dir(Direction::UP) {

    }

	void Ball::setBallRect(int cx, int cy, int cw, int ch) {
		x = cx;
		y = cy;
		w = cw;
		h = ch;
	}

	void Ball::setRect(SDL_Rect *rc) {
		rc->x = x;
		rc->y = y;
		rc->w = w;
		rc->h = h;
	}

	void Ball::setDirection(Direction d) {
		dir = d;
	}

	void Ball::draw() {

	}

    Grid::Grid() {

    }

    Game::Game() : player((1280/2)-75, 600, 150, 10), white(0x0) {

    }

    void Game::init() {
    	white = SDL_MapRGB(game::front->format, 255, 255, 255);
    	ball.setBallRect((1280/2)-8, (720/2), 8, 8);
    }

    void Game::restorePos() {
    	player.x = (1280/2)-75;
    	player.y = 600;
    	ball.x = (1280/2);
    	ball.y = 720/2;
    	ball.w = 16;
    	ball.h = 16;
    }

    void Game::draw() {
    	SDL_Rect rc;
    	player.setRect(&rc);
    	SDL_FillRect(game::front, &rc, white);
    	ball.setRect(&rc);
    	SDL_FillRect(game::front, &rc, white);
    }

}
