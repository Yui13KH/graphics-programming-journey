#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h> // Required in SDL3 for the main hook
#include <stdio.h>

int main(int argc, char* argv[]) {
    // Force console output to be unbuffered so we see it immediately
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("Starting SDL3 Boilerplate...\n");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return -1;
    }

    printf("SDL Initialized successfully!\n");

    printf("Press Enter to exit...");
    getchar();

    SDL_Quit();
    return 0;
}

