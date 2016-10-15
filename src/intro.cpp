#include "intro.hpp"
#include "start.hpp"

namespace intro {
    
    Intro game_intro;
    
    Intro::~Intro() {
        
        if(lostlogo)
            SDL_FreeSurface(lostlogo);
        
        if(jblogo)
            SDL_FreeSurface(jblogo);
        
    }
    
    void Intro::loadData() {
        lostlogo = game::LoadBMP(game::appPath("img/lostlogo.bmp"));
        jblogo = game::LoadBMP(game::appPath("img/jaredblogo.bmp"));
    }
    
    void Intro::draw() {
        static int drawn_start = 0;
        static unsigned int start_time = 0;
        static float direction = 0.05f;
        static const int wait_time = 2000;
        if(start_time == 0) {
            start_time = SDL_GetTicks();
            direction = 0.05f;
        }
    
        if(drawn_start == 0) {
            static float alpha = 0.0f;
            unsigned int cur = SDL_GetTicks();
            
            if(direction == 0.05f && alpha >= 1.0f) {
                if(cur-start_time >= wait_time) {
                    start_time = SDL_GetTicks();
                    direction = -0.05f;
                }
            }
            else if (alpha <= 0 && direction == -0.05f) {
                direction = 0.05f;
                start_time = SDL_GetTicks();
                drawn_start = 1;
            }
            else
            if((cur-start_time) > 25) {
                alpha += direction;
                start_time = SDL_GetTicks();
            }
            
            game::gfx::FadeBlend(lostlogo, game::front, alpha);
            
        } else if(drawn_start == 1) {
            static float alpha = 0.0f;
            unsigned int cur = SDL_GetTicks();
            
            if(direction == 0.05f && alpha >= 1.0f) {
                if(cur-start_time >= wait_time) {
                    start_time = SDL_GetTicks();
                    direction = -0.05f;
                }
            }
            else if (alpha <= 0 && direction == -0.05f) {
                direction = 0.05f;
                start_time = SDL_GetTicks();
                drawn_start = 0;
                game::setScreen(&start::game_start);
            }
            else
            if((cur-start_time) > 25) {
                alpha += direction;
                start_time = SDL_GetTicks();
        	}
            game::gfx::FadeBlend(jblogo, game::front, alpha);
        }
    }
    
    void Intro::update() {
        
    }
    
    void Intro::keydown(int key) {
        
    }
    
    void Intro::keyup(int key) {
        
    }
    
}
