#include <SDL3/SDL.h>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Color {
    uint8_t a, r, g, b;
    uint32_t pack() const {
        return (a << 24) | (r << 16) | (g << 8) | b;
    }
};

struct Rect {
    float x, y, w, h;
    bool contains(float px, float py) const {
        return (px >= x && px < x + w && py >= y && py < y + h);
    }
};

struct Circle {
    float cx, cy, r;
    bool contains(float px, float py) const {
        float dx = px - cx;
        float dy = py - cy;
        return (dx * dx + dy * dy) < (r * r);
    }
};

enum class ShapeType { RECT, CIRCLE };

struct GameObject {
    ShapeType type;
    union {
        Rect rect;
        Circle circle;
    } data;
    Color color;
    float vx, vy;

    bool contains(float px, float py) const {
        if (type == ShapeType::RECT) return data.rect.contains(px, py);
        if (type == ShapeType::CIRCLE) return data.circle.contains(px, py);
        return false;
    }
};

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Bouncing Square", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Surface* screen = SDL_GetWindowSurface(window);

    GameObject player = {.type = ShapeType::RECT,
                         .data = {.rect = {100, 100, 50, 50}},
                         .color = {255, 181, 131, 141},
                         .vx = 0.8f, 
                         .vy = 1.0f};

    bool isRunning = true;
    SDL_Event event;
    Color backgroundColor = {255, 126, 33, 67};

    float frequency = 0.01f;  // How wavy it is
    float amplitude = 20.0f;  // Height of the wave
    float centerY = SCREEN_HEIGHT / 2.0f;
    float centerX = SCREEN_WIDTH / 2.0f;
    float timer = 0.0f;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) isRunning = false;
        }

        if (player.data.rect.x + player.data.rect.w >= SCREEN_WIDTH || player.data.rect.x <= 0) {
            player.vx *= -1;  
        } // basically how the bounce work u just multiply by -1 if u reach the borders

        timer += 0.01f;
        amplitude += 0.1f;
        player.data.rect.x = centerX + std::cos(timer) * amplitude;
        player.data.rect.y = centerY + std::sin(timer) * amplitude;

        SDL_LockSurface(screen);
        uint32_t* pixels = (uint32_t*)screen->pixels;

        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                int index = y * SCREEN_WIDTH + x;

                if (player.contains((float)x, (float)y)) {
                    pixels[index] = player.color.pack();
                } else {
                    pixels[index] = backgroundColor.pack();
                }
            }
        }
        SDL_UnlockSurface(screen);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}