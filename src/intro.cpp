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
        
        lostlogo = SDL_LoadBMP(game::appPath("img/lostlogo.bmp").c_str());
        if(!lostlogo) {
            std::cerr << "Error could not load image: img/lostlogo.bmp\n";
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        
        jblogo = SDL_LoadBMP(game::appPath("img/jaredblogo.bmp").c_str());
        if(!jblogo) {
            std::cerr << "Error could not load image: img/jaredblogo.bmp\n";
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        
    }
    
    void Intro::draw() {
        static int drawn_start = 0;
        static unsigned int start_time = 0;
        
        if(start_time == 0) {
            start_time = SDL_GetTicks();
        }
    
        if(drawn_start == 0) {
            SDL_BlitSurface(lostlogo, 0, game::front, 0);
            unsigned int cur = SDL_GetTicks();
            if(cur-start_time > 3000) {
                drawn_start = 1;
                start_time = SDL_GetTicks();
            }
            
        } else if(drawn_start == 1) {
            SDL_BlitSurface(jblogo, 0, game::front, 0);
            unsigned int cur = SDL_GetTicks();
            if(cur-start_time > 3000) {
                drawn_start = 0;
                start_time = 0;
                //game::_object = &start::game_start;
                game::setScreen(&start::game_start);
            }
        }
    }
    
    void Intro::update() {
        
    }
    
    void Intro::keydown(int key) {
        
    }
    
    void Intro::keyup(int key) {
        
    }
    
}
