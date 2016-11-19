#ifndef __START_H__
#define __START_H__

#include"game.hpp"

namespace start {

	extern SDL_Surface *bg;
	extern SDL_Surface *breakout1;

    class Start : public game::GameObject {
    public:
        virtual ~Start();
        virtual void loadData();
        virtual void draw();
        virtual void update();
        virtual void keydown(int key);
        virtual void keyup(int key);
        void enterPressed();
    private:
        SDL_Surface *_start,*about,*_exit, *title;
        SDL_Color tcolor;
        float alpha;
        int cursor_pos;
    };

    extern Start game_start;
    extern TTF_Font *monaco;
}

#endif
