#include "game.hpp"

namespace game {

	SDL_Window *window;
	SDL_Renderer *render;
	SDL_Texture *tex;
	SDL_Surface *front;

    GameObject *_object;

	void render_game() {
        SDL_FillRect(front, 0, SDL_MapRGB(front->format, 0, 0, 0));
        SDL_LockTexture(tex, 0, &front->pixels, &front->pitch);
        SDL_UnlockTexture(tex);
        
        // - copy
        SDL_RenderCopy(render, tex, 0, 0);
        // draw
        _object->draw();
        SDL_RenderPresent(render);
        
        SDL_Delay(6);
	}

    void keydown_game(int key) {
        _object->keydown(key);
    }
    
    void keyup_game(int key) {
        _object->keyup(key);
    }
    
}
