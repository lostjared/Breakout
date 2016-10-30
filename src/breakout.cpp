#include "breakout.hpp"

namespace breakout {
    
    Breakout game_breakout;
    
    Breakout::~Breakout() {
    	if(ball)
    		SDL_FreeSurface(ball);
    }
    
    void Breakout::loadData() {
        ball = game::LoadBMP(game::appPath("img/ball.bmp"));
        SDL_SetColorKey(ball, SDL_TRUE, SDL_MapRGB(ball->format, 0, 0, 0));
        the_game.init();
    }
    
    void Breakout::draw() {
        the_game.draw();
        SDL_Rect rc;
        the_game.ball.setRect(&rc);
        rc.w = 10;
        rc.h = 10;
        SDL_BlitSurface(ball, 0, game::front, &rc);
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
        
        the_game.update();
        
    }
    
    void Breakout::keydown(int key) {
        
    }
    
    void Breakout::keyup(int key) {
        
    }
    
    Brick::Brick() : brick_type(0), visible(false), color(0x0) {
        
    }
    
    void Brick::setVisible(const bool &b) {
        visible = b;
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
    
    void Brick::setColor(unsigned int col) {
    	color = col;
    }
    unsigned int Brick::getColor() {
    	return color;
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
    
    Ball::Ball() : x(0), y(0), w(0), h(0), d(1), speed(4) {
        
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
    
    void Ball::draw() {
        
    }
    
    Grid::Grid() {
        
    }
    
    void Grid::initBricks() {
    	for(unsigned int i = 0; i < BRICK_W; ++i)
    		for(unsigned int z = 0; z < BRICK_H; ++z) {
    			bricks[i][z].setVisible(true);
    			bricks[i][z].setType(1);
    			bricks[i][z].setColor(SDL_MapRGB(game::front->format, 100+rand()%155, 100+rand()%155, 100+rand()%155));
    		}
    }


    Game::Game() : player((1280/2)-75, 600, 150, 10), white(0x0) {

    }
    
    void Game::init() {
        white = SDL_MapRGB(game::front->format, 255, 255, 255);
        ball.setBallRect((1280/2)-8, (720/2), 10, 10);
        grid.initBricks();
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
        for(unsigned int i = 0; i < Grid::BRICK_W; ++i) {
        	for(unsigned int z = 0; z < Grid::BRICK_H; ++z) {
        		SDL_Rect rc;
        		rc.x = i*Grid::BRICK_SIZE_W+3;
        		rc.y = z*Grid::BRICK_SIZE_H+3;
        		rc.w = Grid::BRICK_SIZE_W-3;
        		rc.h = Grid::BRICK_SIZE_H-3;
        		if(grid.bricks[i][z].visible)
        			SDL_FillRect(game::front, &rc, grid.bricks[i][z].color);
        	}
        }
    }
    void Game::update() {

    	if(ball.x >= player.x && ball.y >= player.y && ball.x <= player.x+player.w && ball.y <= player.y+player.h) {
    		if(ball.x >= player.x && ball.x <= (player.x+(player.w/2))) {
    			ball.d = 3;
    			ball.y -= ball.speed;
    		} else {
    			ball.d = 1;
    			ball.y -= ball.speed;
    		}
    	}
    	else
         if(ball.d == 1 && ball.x > 5 && ball.y > 5) {
            if(ball.x < 10) {
                ball.d = 3;
            }
            else {
                ball.x -= ball.speed;
                ball.y -= ball.speed;
            }
            
        } else if(ball.d == 2 && ball.x > 5 && ball.y < 710) {

            if(ball.x < 10) {
                ball.d = 4;
            } else {
                ball.x -= ball.speed;
                ball.y += ball.speed;
            }
        } else if(ball.d == 3 && ball.x < 1270 && ball.y > 10) {

        	if(ball.x > 1260)
                ball.d = 1;
            else {
                ball.x += ball.speed;
                ball.y -= ball.speed;
            }
        } else if(ball.d == 4 && ball.x < 1270 && ball.y < 710)  {
            if(ball.x > 1260) {
                ball.d = 2;
            }
            else {
                ball.x += ball.speed;
                ball.y += ball.speed;
            }
        } else {

        	if(ball.y > 705) {
        		std::cout << "Round was lost here..\n";
        	}

        	if(ball.d == 1 || ball.d == 3) ball.d++;
            else if(ball.d == 2 || ball.d == 4) ball.d--;
        }
        
    }
    
    
}
