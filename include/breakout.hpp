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
		friend class Game;
	protected:
		int x,y,w,h;

	};

	class Ball {
	public:
		Ball();
		void setBallRect(int cx, int cy, int cw, int ch);
		void setRect(SDL_Rect *rc);
		friend class Game;
		void draw();
	protected:
		int x,y,w,h;
		int d, speed;
	};


	class Grid {
	public:

		static const unsigned int BRICK_W=(1280/32);
		static const unsigned int BRICK_H=(200/16);

		Grid();

		void initBricks();

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

		Grid grid;
		Paddle player;
		Ball ball;
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
