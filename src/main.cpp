#include"intro.hpp"
#include"start.hpp"
#include"breakout.hpp"

int game::width=1280;
int game::height=720;

void Init(int width, int height);
void Release();

int main(int argc, char **argv) {
    
    if(argc == 4) {
        game::width = atoi(argv[2]);
        game::height = atoi(argv[3]);
        if(game::width < 0 || game::height < 0) {
            std::cerr << "Invalid width/height\n";
            exit(EXIT_FAILURE);
        }
        game::path = argv[1];
    }
    else if(argc == 3) {
        game::width = atoi(argv[1]);
        game::height = atoi(argv[2]);
        if(game::width < 0 || game::height < 0) {
            std::cerr << "Invalid width/height\n";
            exit(EXIT_FAILURE);
        }
    }
    else if(argc != 1) {
        std::cerr << "Invalid arguments..\n" << argv[0] << " path width height\n";
        exit(EXIT_FAILURE);
    }
    
    Init(game::width, game::height);
    //game::_object = &intro::game_intro;
    game::setScreen(&intro::game_intro);
    
    
    SDL_Event e;
    bool active = true;
    
    while(active) {
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    active = false;
                    break;
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym == SDLK_ESCAPE) active = false;
                    game::keydown_game(e.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    game::keyup_game(e.key.keysym.sym);
                    break;
                    
            }
        }
        game::render_game();
    }
    
    Release();
	return 0;
}

void Init(int width, int height) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error initalizing SDL: " << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }
    game::window = SDL_CreateWindow("Breakout", 0, 0, width, height, SDL_WINDOW_SHOWN);
    if(game::window == 0) {
        std::cerr << "Error creating window: " << SDL_GetError() << "\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    game::render = SDL_CreateRenderer(game::window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(game::render == 0) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << "\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    game::tex = SDL_CreateTexture(game::render, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 1280, 720);
    
    game::front = SDL_CreateRGBSurfaceFrom(NULL, 1280, 720, 32, 0, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    
    if(TTF_Init() == -1) {
        std::cerr << "Error initalizing font library.\n";
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    game::game_font = TTF_OpenFont(game::appPath("bold.ttf").c_str(), 14);
    if(!game::game_font) {
        std::cerr << "Could not Open Font: " << TTF_GetError() << "\n";
        TTF_Quit();
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    intro::game_intro.loadData();
    breakout::game_breakout.loadData();
    start::game_start.loadData();
}


void Release() {
    TTF_CloseFont(game::game_font);
    TTF_Quit();
    SDL_DestroyRenderer(game::render);
    SDL_DestroyTexture(game::tex);
    SDL_DestroyWindow(game::window);
    SDL_FreeSurface(game::front);
    SDL_Quit();
}
