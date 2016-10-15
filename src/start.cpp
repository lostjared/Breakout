#include"start.hpp"

namespace start {
  
    Start game_start;
    
    Start::~Start() {
        
        if(text != 0)
        SDL_FreeSurface(text);
    }
    
    void Start::loadData() {
        fnt_color.r = fnt_color.g = fnt_color.b = 255;
        text = TTF_RenderText_Solid(game::game_font, "Debug Mode", fnt_color);
        if(!text) {
            std::cerr << "Error rendering text: " << TTF_GetError() << "\n";
            TTF_Quit();
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        
    }
    
    void Start::draw() {
        SDL_Rect pos = { 10, 10, text->w, text->h };
        SDL_BlitSurface(text, 0, game::front, &pos);
    }
    
    void Start::update() {
        
    }
    
    void Start::keydown(int key) {
        
    }
    
    void Start::keyup(int key) {
        
    }
}
