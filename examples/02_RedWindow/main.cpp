#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <cstdint> // for unsigned int 32

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("Cpu Rasterizer 0.1", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Surface *screen =
      SDL_GetWindowSurface(window); // ram based pixels of the window we passed

  bool isRunning = true;
  SDL_Event event;

  while (isRunning) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT)
        isRunning = false;
    }

    SDL_LockSurface(screen);

    uint32_t *pixels = (uint32_t *)screen->pixels;

    // loop over all pixels

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      for (int x = 0; x < SCREEN_WIDTH; x++) {
        int index = (y * SCREEN_WIDTH) + x;

        uint8_t r = (uint8_t)126;
        uint8_t g = (uint8_t)33;
        uint8_t b = (uint8_t)67;

        pixels[index] = (255 << 24) | (r << 16) | (g << 8) | b;
      }
    }

    SDL_UnlockSurface(screen);

    SDL_UpdateWindowSurface(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}