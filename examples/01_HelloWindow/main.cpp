#include <core/Common.hpp>
#include <SDL3/SDL.h>

int main(int argc, char* argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Window 01", 640, 480, 0);
    
    if (window) {
        SDL_Delay(2000); // Show it for 2 seconds
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}