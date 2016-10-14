#ifndef __GAME__H_
#define __GAME__H_
#include "SDL.h"
#include<iostream>
#include<string>

namespace game {
    
    extern SDL_Window *window;
    extern SDL_Renderer *render;
    
    extern SDL_Texture *tex;
    extern SDL_Surface *front;
    
    extern int width, height;
    
    void render_game();
    void keydown_game(int key);
    void keyup_game(int key);
    
    class GameObject {
    public:
        virtual void loadData() = 0;
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void keydown(int key) = 0;
        virtual void keyup(int key) = 0;
    };
    
    extern GameObject *_object;
}






#endif
