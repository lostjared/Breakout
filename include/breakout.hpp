#ifndef __BREAKOUT_H__
#define __BREAKOUT_H__

#include"game.hpp"

namespace breakout {

	class Brick {
	public:
		Brick();
		void setVisible(const bool &b);
		bool isVisible() const;
		int getType() const;
		void setType(const int &b);
		void setColor(unsigned int col);
		unsigned int getColor();
		friend class Game;
	protected:
		int brick_type;
		bool visible;
		unsigned int color;
	};

	enum class Direction { LEFT, UP_LEFT, UP_RIGHT, RIGHT, DOWN_LEFT, DOWN_RIGHT, UP, DOWN };

	enum { PADDLE_SPEED = 8 };

	class Paddle {
	public:
		Paddle(int cx, int cy, int cw, int ch);
		void move(Direction dir);
		void draw();
		void setRect(SDL_Rect *rc);
		void resetPosition();
		friend class Game;
	protected:
		int x,y,w,h;

	};

	class Ball {
	public:

		static const int MAX_BALL=5;

		Ball();
		void setBallRect(int cx, int cy, int cw, int ch);
		void setRect(SDL_Rect *rc);
		friend class Game;
		void draw();
		void setActive(const bool &state);
		bool getActive() const { return active; }
		void resetPosition();
	protected:
		int x,y,w,h;
		int d, speed;
		bool active;
	};


	class Grid {
	public:

		static const unsigned int BRICK_SIZE_W=64;
		static const unsigned int BRICK_SIZE_H=16;
		static const unsigned int BRICK_W=(1280/BRICK_SIZE_W);
		static const unsigned int BRICK_H=(100/BRICK_SIZE_H);

		Grid();
		void initBricks();

		friend class Game;

	protected:
		Brick bricks[BRICK_W][BRICK_H];

	};

	class Game {
	public:
		Game();
		void init();
		void draw();
		void restorePos();
		void update();
		void releaseBall();
		void newGame();

		Grid grid;
		Paddle player;
		Ball ball[Ball::MAX_BALL];
		Uint32 white;
	};

    class Breakout : public game::GameObject {
    public:
        virtual ~Breakout();
        virtual void loadData();
        virtual void draw();
        virtual void update();
        virtual void keydown(int key);
        virtual void keyup(int key);
    private:
        Game the_game;
        SDL_Surface *ball;
    };
    
    extern Breakout game_breakout;
}

#endif
