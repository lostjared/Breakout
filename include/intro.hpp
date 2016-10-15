#ifndef __INTRO__H__
#define __INTRO__H__

#include "game.hpp"

namespace intro {
    
    class Intro : public game::GameObject {
    public:
        virtual ~Intro();
        virtual void loadData();
        virtual void draw();
        virtual void update();
        virtual void keydown(int key);
        virtual void keyup(int key);
    private:
        SDL_Surface *lostlogo, *jblogo;
    };
   
    extern Intro game_intro;
}


#endif
