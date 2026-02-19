#include "Screen.hpp"

Screen::Screen() : width{0}, height{0} {
    // placeholder
}

Screen::Screen(uint32_t w, uint32_t h) : Screen() {
    this->width = w;
    this->height = h;
    this->surface = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_RGBA32);
    if (!this->surface) {
        std::cerr << SDL_GetError();
        exit(1);
    }
    this->drawBox(ivec2(0, 0), ivec2(this->width, this->height), ivec3(0, 0, 0));
}

Screen::Screen(const Screen& cp) : Screen() {
    this->width = cp.width;
    this->height = cp.height;
    this->surface = SDL_CreateSurface(this->width, this->height, SDL_PIXELFORMAT_RGBA32);
    if (!this->surface) {
        std::cerr << SDL_GetError();
        exit(1);
    }
    
    // must copy over the exact pixels from cp's surface to this surface
    if (this->surface) {
        cp.blitTo(this->surface);
    }
}

Screen::~Screen() {
    if (this->surface != nullptr) {
        SDL_DestroySurface(this->surface);
    }
}


Screen& Screen::operator=(const Screen& cp) {
    if ((this->surface->format != cp.surface->format) || (this->width != cp.width) || (this->height != cp.height)) {
        std::cerr << "Surfaces not compatible\n";
        return *this;
    }

    this->width = cp.width;
    this->height = cp.height;
    this->surface = SDL_CreateSurface(this->width, this->height, SDL_PIXELFORMAT_RGBA32);
    if (!this->surface) {
        std::cerr << SDL_GetError();
        exit(1);
    }
    
    cp.blitTo(this->surface);
    
    return *this;
}

void Screen::blitTo(SDL_Surface* target) const {
    if (target == nullptr) {
        std::cerr << "Target surface is a nullptr.\n";
        return;
    }
    bool success = SDL_BlitSurface(this->surface, nullptr, target, nullptr);
    if (!success) {
        std::cerr << SDL_GetError();
    }
}

void Screen::drawBresenhamLine(ivec2 start, ivec2 end, ivec3 color) {
    int x0 = start.x;
    int y0 = start.y;
    int x1 = end.x;
    int y1 = end.y;

    int dx = std::abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1; // sign(+/-) of x

    int dy = -std::abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1; // sign(+/-) of y

    int error = dx + dy;

    
    while (true) {
        if ((x0 >= 0) && (x0 < this->width) && (y0 >= 0) && (y0 < this->height)) {
            colorOnePixel(ivec2(x0, y0),color);
        }

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



