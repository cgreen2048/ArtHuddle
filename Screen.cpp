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
    // if ((this->surface->format == cp.surface->format) && (this->width == cp.width) && (this->height == cp.height)) {
    //     int minX = 0;
    //     int maxX = this->width;
    //     int minY = 0;
    //     int maxY = this->height;

    //     bool same = true;
    //     for (int i = minX; i <= maxX; ++i) {
    //         for (int j = minY; j <= maxY; ++j) {
    //             uint8_t* pixelPtr = static_cast<uint8_t*>(this->surface->pixels);
    //             uint8_t* pixel = pixelPtr 
    //                 + static_cast<int>(i) * sizeof(uint32_t) 
    //                 + static_cast<int>(j) * this->surface->pitch;
    //             uint32_t* pixel32 = reinterpret_cast<uint32_t*>(pixel);

    //             uint8_t* cpPixelPtr = static_cast<uint8_t*>(cp.surface->pixels);
    //             uint8_t* cpPixel = cpPixelPtr 
    //                 + static_cast<int>(i) * sizeof(uint32_t) 
    //                 + static_cast<int>(j) * cp.surface->pitch;
    //             uint32_t* cpPixel32 = reinterpret_cast<uint32_t*>(cpPixel);

    //             if (pixel32 != cpPixel32) same = false;
    //         }
    //     }
    //     if (same) {
    //         std::cout << "same\n";
    //         return *this;
    //     }
    // }

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

    if ((x0 < 0) || (x0 > this->width - 1) || (y0 < 0) || (y0 > this->height - 1)) {
        std::cerr << "Line start point is out of bounds\n";
        return;
    }
    if ((x1 < 0) || (x1 > this->width - 1) || (y1 < 0) || (y1 > this->height - 1)) {
        std::cerr << "Line end point is out of bounds\n";
        return;
    }
    if ((color.x < 0) || (color.x > 255) || (color.y < 0) || (color.y > 255) || (color.z < 0) || (color.z > 255)) {
        std::cerr << "Invalid color value\n";
        return;
    }

    int dx = std::abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1; // sign(+/-) of x

    int dy = -std::abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1; // sign(+/-) of y

    int error = dx + dy;

    
    while (true) {
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



