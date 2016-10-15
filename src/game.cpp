#include "game.hpp"

namespace game {

	SDL_Window *window;
	SDL_Renderer *render;
	SDL_Texture *tex;
	SDL_Surface *front;
    TTF_Font *game_font;

    GameObject *_object;
    std::string path;

	void render_game() {
        SDL_FillRect(front, 0, SDL_MapRGB(front->format, 0, 0, 0));
        SDL_LockTexture(tex, 0, &front->pixels, &front->pitch);
        SDL_UnlockTexture(tex);
        SDL_Rect dst = { 0,0,width,height };
        SDL_RenderCopy(render, tex, 0, &dst);
        // draw
        _object->draw();
        
        SDL_RenderPresent(render);
        
        SDL_Delay(15);
	}

    void keydown_game(int key) {
        _object->keydown(key);
    }
    
    void keyup_game(int key) {
        _object->keyup(key);
    }
    
    void setScreen(GameObject *obj) {
        _object = obj;
    }
    
    std::string appPath(const std::string &p) {
        return path+"/"+p;
    }
    
    SDL_Surface *LoadBMP(const std::string &text) {
        SDL_Surface *bmp = SDL_LoadBMP(text.c_str());
        if(!bmp) {
            std::cerr << "Error loading image: " << text << "\n";
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        
        SDL_Surface *temp = SDL_ConvertSurfaceFormat(bmp, front->format->format, 0);
        if(!temp) {
            std::cerr << "Error converting to Display Format..\n";
            SDL_Quit();
            exit(EXIT_FAILURE);
        }
        
        SDL_FreeSurface(bmp);
        return temp;
    }
    
}
