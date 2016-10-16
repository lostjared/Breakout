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
        _object->update();
        
        SDL_RenderPresent(render);
        
        SDL_Delay(10);
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
        SDL_Surface *bmp = IMG_Load(text.c_str());
        if(!bmp) {
            std::cerr << "Error loading image: " << text << " " << IMG_GetError() << "\n";
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
        std::cout << "Successfully loaded image: " << text << "\n";
        return temp;
    }
    
    
    namespace gfx {
        
        void FadeBlend(SDL_Surface *bmp1, SDL_Surface *dst, float alpha) {
            if((bmp1->w != dst->w) ||  (bmp1->h != dst->h)) {
                std::cerr << "Invalid surface size..\n";
                SDL_Quit();
                exit(EXIT_FAILURE);
            }
            if((bmp1->format->BitsPerPixel != 32)||(dst->format->BitsPerPixel != 32)) {
                std::cerr << "Invalid bpp.\n";
                SDL_Quit();
                exit(EXIT_FAILURE);
            }
            // start
            if(SDL_MUSTLOCK(dst)) {
                SDL_LockSurface(dst);
            }
            
            if(SDL_MUSTLOCK(bmp1)) {
                SDL_LockSurface(bmp1);
            }
            for(unsigned int i = 0; i < dst->w; ++i) {
                for(unsigned int z = 0; z < dst->h; ++z) {
                    unsigned int *buf1 = (unsigned int*)bmp1->pixels+(i+z*bmp1->w);
                    unsigned int *target = (unsigned int*)dst->pixels+(i+z*dst->w);
                    unsigned char *pix1 = (unsigned char*)buf1;
                    unsigned char rgb[3];
                    rgb[0] = pix1[0] * alpha;
                    rgb[1] = pix1[1] * alpha;
                    rgb[2] = pix1[2] * alpha;
                    *target = SDL_MapRGB(dst->format, rgb[2], rgb[1], rgb[0]);
                }
            }
            // stop
            if(SDL_MUSTLOCK(dst)) {
                SDL_UnlockSurface(dst);
            }
            
            if(SDL_MUSTLOCK(bmp1)) {
                SDL_UnlockSurface(bmp1);
            }
        }


        void BlendWithFront(int x, int y, SDL_Surface *bmp1, SDL_Surface *dst, float alpha) {
             if((bmp1->format->BitsPerPixel != 32)||(dst->format->BitsPerPixel != 32)) {
                 std::cerr << "Invalid bpp.\n";
                 SDL_Quit();
                 exit(EXIT_FAILURE);
             }
             // start
             if(SDL_MUSTLOCK(dst)) {
                 SDL_LockSurface(dst);
             }

             if(SDL_MUSTLOCK(bmp1)) {
                 SDL_LockSurface(bmp1);
             }
             for(unsigned int i = 0; i < bmp1->w; ++i) {
                 for(unsigned int z = 0; z < bmp1->h; ++z) {
                     unsigned int *buf1 = (unsigned int*)bmp1->pixels+(i+z*bmp1->w);
                     unsigned int *target = (unsigned int*)dst->pixels+((x+i)+(z+y)*dst->w);
                     unsigned char *pix1 = (unsigned char*)buf1;
                     unsigned char *pix2 = (unsigned char*)target;
                     unsigned char rgb[3];
                     rgb[0] = pix2[0]+(pix1[0] * alpha);
                     rgb[1] = pix2[1]+(pix1[1] * alpha);
                     rgb[2] = pix2[2]+(pix1[2] * alpha);
                     *target = SDL_MapRGB(dst->format, rgb[2], rgb[1], rgb[0]);
                 }
             }
             // stop
             if(SDL_MUSTLOCK(dst)) {
                 SDL_UnlockSurface(dst);
             }

             if(SDL_MUSTLOCK(bmp1)) {
                 SDL_UnlockSurface(bmp1);
             }
        }
    }
    
}
