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

    class Breakout : public game::GameObject {
    public:
        virtual ~Breakout();
        virtual void loadData();
        virtual void draw();
        virtual void update();
        virtual void keydown(int key);
        virtual void keyup(int key);
    };
    
    extern Breakout game_breakout;
}

#endif
