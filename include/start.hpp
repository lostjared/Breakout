#ifndef __START_H__
#define __START_H__

#include"game.hpp"

namespace start {
    
    class Start : public game::GameObject {
    public:
        virtual ~Start();
        virtual void loadData();
        virtual void draw();
        virtual void update();
        virtual void keydown(int key);
        virtual void keyup(int key);
        void BlendImage(SDL_Surface *src, SDL_Surface *dst);
        void enterPressed();
    private:
        SDL_Surface *title;
        SDL_Surface *bg,*_start,*about,*_exit;
        SDL_Color tcolor;
        float alpha;
        int cursor_pos;
    };

    extern Start game_start;
    extern TTF_Font *monaco;
}

#endif
