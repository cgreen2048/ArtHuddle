#include "screen.hpp"

Screen::Screen() : width{0}, height{0} {
    // placeholder
}

Screen::Screen(uint32_t w, uint32_t h) : Screen() {
    width = w;
    height = h;
    surface = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGBA32);
}

Screen::Screen(const Screen& cp) : Screen() {
    width = cp.width;
    height = cp.height;
    surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    
    // must copy over the exact pixels from cp's surface to this surface
    if (surface) {
        cp.blitTo(surface);
    }
}

Screen::Screen~() {
    if (surface != nullptr) {
        SDL_DestroySurface(surface);
    }
}

Screen& Screen::operator=(const Screen& cp) {
    if (*this == cp) {
        return *this;
    }

    width = cp.width;
    height = cp.height;
    surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
    
    if (surface) {
        cp.blitTo(surface);
    }
}

void Screen::colorOnePixel(vec2 coords, vec3 colors) {
    uint8_t* pixelPtr = static_cast<uint8_t*>(surface->pixels);
    uint8_t* pixel = pixelPtr 
        + static_cast<int>coords.x * sizeof(uint32_t) 
        + static_cast<int>coords.y * surface->pitch;
    uint32_t* pixel32 = reinterpret_cast<uint32_t*>(pixel);
    uint32_t pixelColor = SDL_MapRGBA(
        surface->format, 
        static_cast<int>colors.x, 
        static_cast<int>colors.y, 
        static_cast<int>colors.z, 
        static_cast<int>ALPHA_VALUE
    );
    
    *pixel32 = pixelColor;
}
