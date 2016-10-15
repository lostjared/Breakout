#ifndef __START_H__
#define __START_H__

#include"game.hpp"

namespace start {
    
    class Start : public game::GameObject {
    public:
        Start() = default;
        virtual ~Start();
        virtual void loadData();
        virtual void draw();
        virtual void update();
        virtual void keydown(int key);
        virtual void keyup(int key);
    private:
        SDL_Surface *text;
        SDL_Color fnt_color;
        SDL_Surface *title;
    };

    extern Start game_start;
}

#endif
