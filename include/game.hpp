#ifndef __GAME__H_
#define __GAME__H_

// so i don't have to watch the intro a million times
#define DEBUG_MODE

#include "SDL.h"
#include "SDL_ttf.h"
#include <SDL/SDL_image.h>
#include<iostream>
#include<string>
#include<unistd.h>
#include<ctime>
#include<cstdlib>

namespace game {
    
    extern SDL_Window *window;
    extern SDL_Renderer *render;
    
    extern SDL_Texture *tex;
    extern SDL_Surface *front;
    
    extern TTF_Font *game_font;
    
    extern int width, height;
    extern std::string path;
    
    void render_game();
    void keydown_game(int key);
    void keyup_game(int key);
    
    class GameObject {
    public:
    	virtual ~GameObject() {}
        virtual void loadData() = 0;
        virtual void draw() = 0;
        virtual void update() = 0;
        virtual void keydown(int key) = 0;
        virtual void keyup(int key) = 0;
    };
    
    extern GameObject *_object;
    void setScreen(GameObject *obj);
    std::string appPath(const std::string &text);
    SDL_Surface *LoadBMP(const std::string &text);
    
    namespace gfx {
        void FadeBlend(SDL_Surface *bmp1, SDL_Surface *dst, float alpha);
        void BlendWithFront(int x, int y, SDL_Surface *bmp1, SDL_Surface *dst, float alpha);
    }
}






#endif
