#include <SDL3/SDL.h>

#include <cmath>
#include <cstdint>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Color {
    uint8_t a, r, g, b;
    uint32_t pack() const {
        return (a << 24) | (r << 16) | (g << 8) | b;
    }
};

struct Rect {
    float x, y, width, height, angle;
    Color color;

    bool contains(int px, int py) const {
        float rad = -angle * (M_PI / 180.0f);
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);
        float cx = x + width / 2.0f;
        float cy = y + height / 2.0f;
        float dx = px - cx;
        float dy = py - cy;
        float rx = dx * cosA - dy * sinA;
        float ry = dx * sinA + dy * cosA;
        return (rx >= -width / 2.0f && rx <= width / 2.0f && ry >= -height / 2.0f &&
                ry <= height / 2.0f);
    }
};

void handleInput(Rect& entity, bool& running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) running = false;
    }

    const bool* keys = SDL_GetKeyboardState(nullptr);
    const float moveSpeed = 2.0f;
    const float rotationSpeed = 2.0f;
    const float growthSpeed = 2.0f;

    if (keys[SDL_SCANCODE_UP]) entity.y -= moveSpeed;
    if (keys[SDL_SCANCODE_DOWN]) entity.y += moveSpeed;
    if (keys[SDL_SCANCODE_LEFT]) entity.x -= moveSpeed;
    if (keys[SDL_SCANCODE_RIGHT]) entity.x += moveSpeed;
    if (keys[SDL_SCANCODE_Q]) entity.angle -= rotationSpeed;
    if (keys[SDL_SCANCODE_E]) entity.angle += rotationSpeed;

    if (keys[SDL_SCANCODE_KP_PLUS]) {
        entity.width += growthSpeed;
        entity.height += growthSpeed;
        entity.x -= growthSpeed / 2.0f;
        entity.y -= growthSpeed / 2.0f;
    }
    if (keys[SDL_SCANCODE_KP_MINUS] && entity.width > 5.0f) {
        entity.width -= growthSpeed;
        entity.height -= growthSpeed;
        entity.x += growthSpeed / 2.0f;
        entity.y += growthSpeed / 2.0f;
    }
}

void clearScreen(uint32_t* pixels, Color color) {
    uint32_t packed = color.pack();
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i) {
        pixels[i] = packed;
    }
}

void renderScene(SDL_Surface* surface, const std::vector<Rect>& entities, Color background) {
    SDL_LockSurface(surface);
    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);

    clearScreen(pixels, background);

    for (int y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int x = 0; x < SCREEN_WIDTH; ++x) {
            for (const auto& entity : entities) {
                if (entity.contains(x, y)) {
                    pixels[y * SCREEN_WIDTH + x] = entity.color.pack();
                }
            }
        }
    }

    SDL_UnlockSurface(surface);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Modular Rasterizer", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Surface* screen = SDL_GetWindowSurface(window);

    Rect player = {
        (SCREEN_WIDTH / 2.0f) - 25.0f, (SCREEN_HEIGHT / 2.0f) - 25.0f, 50.0f, 50.0f, 0.0f,
        {255, 181, 131, 141}};

    Color bg = {255, 126, 33, 67};
    bool isRunning = true;

    while (isRunning) {
        handleInput(player, isRunning);
        renderScene(screen, {player}, bg);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}