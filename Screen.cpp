#include "Screen.hpp"

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

Screen::~Screen() {
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

void Screen::blitTo(SDL_Surface* target){
    if (target == nullptr){
        std::cerr << "Target surface is a nullptr.\n";
        return;
    }
    SDL_BlitSurface(surface, nullptr, target, nullptr); 
}

void Screen::drawBresenhamLine(ivec2 start, ivec2 end, ivec3 color){
    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    int dx = std::abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1; // sign(+/-) of x

    int dy = -std::abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1; // sign(+/-) of y

    int error = dx + dy;

    
    while (true){
        colorOnePixel(ivec2(x0, y0),color);

        if (x0 == x1 && y0 == y1){
            break;
        }

        int e2 = 2 * error;

        if (e2 >= dy){
            error += dy;
            x0 += sx;
        }

        if (e2 <= dx){
            error += dx;
            y0 += sy;
        }
    }     
}



