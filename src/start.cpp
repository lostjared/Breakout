#include"start.hpp"

namespace start {
  
    Start game_start;
    TTF_Font *monaco;
    
    Start::~Start() {
        if(text != 0)
            SDL_FreeSurface(text);
        if(title != 0)
            SDL_FreeSurface(title);
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
        
        tcolor.r = 255;
        tcolor.g = tcolor.b = 0;
        
        title = TTF_RenderText_Solid(monaco, "PSYCHE BREAK", tcolor);
        
        if(!title) {
            std::cerr << "Error rendering text..\n";
            SDL_Quit();
            exit(EXIT_FAILURE);
        }

        bg = game::LoadBMP(game::appPath("img/bg.jpg"));
        alpha = 0.0f;

    }
    
    void Start::BlendImage(SDL_Surface *src, SDL_Surface *dst) {
    	game::gfx::FadeBlend(src, dst, alpha);
    	static unsigned int direction = 0;
    	if(direction == 0) {
        	alpha += 0.05f;
        	if(alpha >= 2.0f) {
        		direction = 1;
        	}

    	}
    	else if(direction == 1) {
    		alpha -= 0.05f;
    		if(alpha <= 1.0f) {
    			direction = 0;
    		}
    	}
    }

    void Start::draw() {
    	BlendImage(bg, game::front);
    	SDL_Rect pos1 = { (game::front->w/2)-(title->w/2), 0, title->w, title->h };
        SDL_BlitSurface(title, 0, game::front, &pos1);
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
