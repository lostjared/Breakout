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
	protected:
		int brick_type;
		bool visible;
	};

	enum class Direction { LEFT, RIGHT, UP, DOWN };

	enum { PADDLE_SPEED = 8 };

	class Paddle {
	public:
		Paddle(int cx, int cy, int cw, int ch);
		void move(Direction dir);
		void draw();
		void setRect(SDL_Rect *rc);
	protected:
		int x,y,w,h;

	};


	class Grid {
	public:
		Grid();
	protected:
		Brick bricks[1280/32][360/16];

	};

	class Game {
	public:
		Game();
		void draw();


		Grid grid;
		Paddle player;
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
    };
    
    extern Breakout game_breakout;
}

#endif
