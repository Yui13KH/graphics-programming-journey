#include <SDL3/SDL.h>
#include <cmath>
#include <vector>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct Color {
    uint8_t a, r, g, b;
    uint32_t pack() const { return (a << 24) | (r << 16) | (g << 8) | b; }
};

struct Rect {
    float x, y, w, h;
    bool contains(float px, float py) const {
        return (px >= x && px < x + w && py >= y && py < y + h);
    }
};

enum class ShapeType { RECT }; // Keeping it simple for 05_collisions

struct GameObject {
    ShapeType type;
    Rect rect; // Removed union for this specific step to keep syntax clean
    Color color;
    float vx, vy;
    bool isStatic; // New: If true, gravity won't affect it (like a floor)

    bool contains(float px, float py) const {
        return rect.contains(px, py);
    }
};

// Simple AABB Collision Check
bool checkCollision(const Rect& a, const Rect& b) {
    return (a.x < b.x + b.w && a.x + a.w > b.x &&
            a.y < b.y + b.h && a.y + a.h > b.y);
}

void updatePhysics(std::vector<GameObject>& entities, float gravity, float friction) {
    for (auto& obj : entities) {
        if (obj.isStatic) continue;

        // Apply Gravity & Movement
        obj.vy += gravity;
        obj.rect.y += obj.vy;

        // Check against every OTHER object (Collision)
        for (auto& other : entities) {
            if (&obj == &other) continue; // Don't collide with self

            if (checkCollision(obj.rect, other.rect)) {
                // If we hit something from above (Floor Collision)
                if (obj.vy > 0) {
                    obj.rect.y = other.rect.y - obj.rect.h; // Snap to top
                    obj.vy *= -1;
                    obj.vy *= friction;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("05_Collisions", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Surface* screen = SDL_GetWindowSurface(window);

    std::vector<GameObject> entities;

    // The Falling Square
    entities.push_back({ShapeType::RECT, {300, 50, 50, 50}, {255, 255, 100, 100}, 0, 0, false});
    entities.push_back({ShapeType::RECT, {320, 50, 50, 50}, {255, 255, 100, 100}, 0, 0, false});
    
    // The Static Floor
    entities.push_back({ShapeType::RECT, {50, 400, 540, 40}, {255, 100, 255, 100}, 0, 0, true});

    bool isRunning = true;
    SDL_Event event;
    Color bg = {255, 30, 30, 30};

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) isRunning = false;
        }

        // 1. Update
        updatePhysics(entities, 0.2f, 0.7f);

        // 2. Render
        SDL_LockSurface(screen);
        uint32_t* pixels = (uint32_t*)screen->pixels;

        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                int index = y * SCREEN_WIDTH + x;
                uint32_t pixelColor = bg.pack();

                for (const auto& obj : entities) {
                    if (obj.contains((float)x, (float)y)) {
                        pixelColor = obj.color.pack();
                        break; 
                    }
                }
                pixels[index] = pixelColor;
            }
        }
        SDL_UnlockSurface(screen);
        SDL_UpdateWindowSurface(window);
        SDL_Delay(16); // Cap to ~60fps
    }

    SDL_Quit();
    return 0;
}