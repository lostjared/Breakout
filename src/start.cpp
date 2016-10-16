#include"start.hpp"
#include"intro.hpp"
#include"breakout.hpp"
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
        _start = game::LoadBMP(game::appPath("img/start.jpg"));
        about = game::LoadBMP(game::appPath("img/about.jpg"));
        _exit = game::LoadBMP(game::appPath("img/exit.jpg"));

        alpha = 0.0f;
        cursor_pos = 0;

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
    			alpha = 1.0f;
    		}
    	}
    }

    void Start::draw() {
    	BlendImage(bg, game::front);
    	SDL_Rect pos1 = { (game::front->w/2)-(title->w/2), 0, title->w, title->h };
        SDL_BlitSurface(title, 0, game::front, &pos1);

        if(alpha >= 1.0f) {
        	SDL_Rect startPos = { 140, 300, _start->w, _start->h };
        	SDL_Rect aboutPos = { 480, 300, about->w, about->h };
        	SDL_Rect exitPos = { 480+320+20, 300, _exit->w, _exit->h };

        	SDL_Rect rct;

        	switch(cursor_pos) {
        	case 0:
        		rct = startPos;
        		break;
        	case 1:
        		rct = aboutPos;
        		break;
        	case 2:
        		rct = exitPos;
        		break;
        	}

        	SDL_FillRect(game::front, &startPos, SDL_MapRGB(game::front->format, rand()%255, rand()%255, rand()%255));
        	SDL_FillRect(game::front, &aboutPos, SDL_MapRGB(game::front->format, rand()%255, rand()%255, rand()%255));
        	SDL_FillRect(game::front, &exitPos, SDL_MapRGB(game::front->format, rand()%255, rand()%255, rand()%255));


        	rct.x -= 20;
        	rct.w += 40;
        	rct.y -= 20;
        	rct.h += 40;

        	SDL_FillRect(game::front, &rct, SDL_MapRGB(game::front->format, rand()%255, rand()%255, rand()%255));

        	static float alpha1 = 1.0f;

        	alpha1 += 0.01f;
        	if(alpha1 > 2) alpha1 = 1.0f;

        	game::gfx::BlendWithFront(startPos.x, startPos.y, _start, game::front, alpha1);
        	game::gfx::BlendWithFront(aboutPos.x, aboutPos.y, about, game::front, alpha1);
        	game::gfx::BlendWithFront(exitPos.x, exitPos.y, _exit, game::front,alpha1);
        }

        SDL_Rect pos = { 10, 10, text->w, text->h };
        SDL_BlitSurface(text, 0, game::front, &pos);



    }
    
    void Start::update() {
        
    }
    
    void Start::enterPressed() {
    	switch(cursor_pos) {
    	case 0:
    		game::setScreen(&breakout::game_breakout);
    		break;
    	case 1:
    		alpha = 0.0f;
    		game::setScreen(&intro::game_intro);
    		break;
    	case 2:
    		TTF_Quit();
    		SDL_Quit();
    		exit(EXIT_SUCCESS);
    		break;
    	}
    }

    void Start::keydown(int key) {
    	switch(key) {
    	case SDLK_LEFT:
    		if(cursor_pos > 0) cursor_pos--;
    		break;
    	case SDLK_RIGHT:
    		if(cursor_pos < 2) cursor_pos++;
    		break;
    	case SDLK_RETURN:
    		enterPressed();
    		break;
    	}
    }
    
    void Start::keyup(int key) {
        
    }
}
