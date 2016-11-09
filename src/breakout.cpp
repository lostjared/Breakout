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
        the_game.newGame();
    }
    
    void Breakout::draw() {
        the_game.draw();
        SDL_Rect rc;

        for(unsigned int i = 0; i < Ball::MAX_BALL; ++i) {

        	if(the_game.ball[i].getActive() == false)
        		continue;

        	the_game.ball[i].setRect(&rc);
        	rc.w = 10;
        	rc.h = 10;
        	SDL_BlitSurface(ball, 0, game::front, &rc);
        }
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
#ifdef DEBUG_MODE
        if(key == SDLK_SPACE)
        	the_game.releaseBall();
#endif
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
    
    void Paddle::resetPosition() {
    	x = 1280/2;
    	y = 600;
    	w = 150;
    	h = 10;
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
//                if(y > 360) y -= (PADDLE_SPEED/2);
                break;
            case Direction::DOWN:
//                if(y < 720-h) y += (PADDLE_SPEED/2);
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
    
    Ball::Ball() : x(1280/2), y(720/2), w(10), h(10), d(1), speed(4), active(false) {

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
    
    void Ball::setActive(const bool &state) {
    	active = state;
    }

    void Ball::resetPosition() {
    	setBallRect(rand()%1260, 720/2, 10, 10);
    	d = ((rand()%2) == 0) ? 1 : 3;
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


    Game::Game() : player((1280/2)-75, 600, 150, 10), white(0x0), level(1), score(0), lives(5) {

    }
    
    void Game::newGame() {
    	level = 1;
    	lives = 5;
    	score = 0;
    	releaseBall();
    	player.resetPosition();
    }

    void Game::init() {
        white = SDL_MapRGB(game::front->format, 255, 255, 255);
       for(unsigned int i = 0; i < Ball::MAX_BALL; ++i)
        ball[i].setBallRect((1280/2)-8, (720/2), 10, 10);
        grid.initBricks();
    }
    
    void Game::restorePos() {
        player.x = (1280/2)-75;
        player.y = 600;

    }
    
    void Game::releaseBall() {
    	for(int i = 0; i < Ball::MAX_BALL; ++i) {
    		if(ball[i].getActive() == false) {
    			ball[i].setActive(true);
    			ball[i].resetPosition();
    			break;
    		}
    	}
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


    	for(int x = 0; x < Grid::BRICK_W; ++x) {
    		for(int y = 0; y < Grid::BRICK_H; ++y) {

    			int cx = x*Grid::BRICK_SIZE_W+3;
    			int cy = y*Grid::BRICK_SIZE_H+3;
    			int cw = Grid::BRICK_SIZE_W-3;
    			int ch = (Grid::BRICK_SIZE_H-3);

    			SDL_Rect rc1 = {cx,cy,cw,ch};


    			for(int q = 0; q < Ball::MAX_BALL; ++q) {
    				if(ball[q].getActive() == false)
    					continue;

    				SDL_Rect rc2 = {ball[q].x, ball[q].y, ball[q].w, ball[q].h};

    				if( (grid.bricks[x][y].isVisible() && rc1.x < rc2.x + rc2.w) && (rc1.y < rc2.y + rc2.h) && (rc2.x < rc1.x + rc1.w) && (rc2.y < rc1.y + rc1.h)) {
    					grid.bricks[x][y].setVisible(false);
    					score += 10;
    					ball[q].d = (rc2.x > rc1.x+(rc1.w/2)) ? 4 : 2;
    				}
    			}


    		}
    	}


    	for(int i = 0; i < Ball::MAX_BALL; ++i) {

    		if(ball[i].getActive() == false)
    			continue;

    		if(ball[i].x >= player.x && ball[i].y >= player.y && ball[i].x <= player.x+player.w && ball[i].y <= player.y+player.h) {
    			if(ball[i].x >= player.x && ball[i].x <= (player.x+(player.w/2))) {
    				//ball[i].d = ((rand()%2) == 0) ? 1 : 3;
    				ball[i].d = 1;
    				ball[i].y -= ball[i].speed;
    			} else {
    				ball[i].d = 3;
    				//ball[i].d = ((rand()%2) == 0) ? 3 : 1;
    				ball[i].y -= ball[i].speed;
    			}
    		}
    		else
    			if(ball[i].d == 1 && ball[i].x > 5 && ball[i].y > 5) {
    				if(ball[i].x < 10) {
    					ball[i].d = 3;
    				}
    				else {
    					ball[i].x -= ball[i].speed;
    					ball[i].y -= ball[i].speed;
    				}

    			} else if(ball[i].d == 2 && ball[i].x > 5 && ball[i].y < 710) {

    				if(ball[i].x < 10) {
    					ball[i].d = 4;
    				} else {
    					ball[i].x -= ball[i].speed;
    					ball[i].y += ball[i].speed;
    				}
    			} else if(ball[i].d == 3 && ball[i].x < 1270 && ball[i].y > 10) {

    				if(ball[i].x > 1260)
    					ball[i].d = 1;
    				else {
    					ball[i].x += ball[i].speed;
    					ball[i].y -= ball[i].speed;
    				}
    			} else if(ball[i].d == 4 && ball[i].x < 1270 && ball[i].y < 710)  {
    				if(ball[i].x > 1260) {
    					ball[i].d = 2;
    				}
    				else {
    					ball[i].x += ball[i].speed;
    					ball[i].y += ball[i].speed;
    				}
    			} else {

    				if(ball[i].y > 705) {
    					ball[i].setActive(false);
    					--lives;
    					if(lives <= 0) {
    						// game over
    					}
    				}

    				if(ball[i].d == 1 || ball[i].d == 3) ball[i].d++;
    				else if(ball[i].d == 2 || ball[i].d == 4) ball[i].d--;
    			}

    	}

    }
}
