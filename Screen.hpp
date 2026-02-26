#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <iostream>
#include <algorithm>
#include <SDL3/SDL.h>
#include <cstring>
#include "vec2.hpp"
#include "vec3.hpp"
#define MIN_COLOR_VALUE 0
#define MAX_COLOR_VALUE 255

class Screen {
    private:
        uint32_t width, height;
        SDL_Surface* surface = nullptr;
        
    public:
        Screen();
        Screen(uint32_t, uint32_t);
        Screen(const Screen&);
        ~Screen();
        Screen& operator=(const Screen&);
        bool operator==(const Screen);
        bool surfaceEqual(const SDL_Surface*);
        void blitTo(SDL_Surface*) const;
        void drawBresenhamLine(ivec2, ivec2, ivec3);
        SDL_Surface* getSurface();
        uint32_t getWidth();
        uint32_t getHeight();

        template<typename T1, typename T2>
        void colorOnePixel(const Tvec2<T1> coords, const Tvec3<T2> colors) {
            if ((coords.x < 0) || (coords.x > this->width - 1) || (coords.y < 0) || (coords.y > this->height - 1)) {
                std::cerr << "Point is out of bounds\n";
                return;
            }
            uint8_t* pixelPtr = static_cast<uint8_t*>(this->surface->pixels);
            uint8_t* pixel = pixelPtr 
                + static_cast<int>(coords.x) * sizeof(uint32_t) 
                + static_cast<int>(coords.y) * this->surface->pitch;
            uint32_t* pixel32 = reinterpret_cast<uint32_t*>(pixel);
            const SDL_PixelFormatDetails *details =  SDL_GetPixelFormatDetails(this->surface->format);
            uint32_t pixelColor = SDL_MapRGBA(
                details,
                nullptr, 
                std::clamp(static_cast<int>(colors.x), MIN_COLOR_VALUE, MAX_COLOR_VALUE), 
                std::clamp(static_cast<int>(colors.y), MIN_COLOR_VALUE, MAX_COLOR_VALUE), 
                std::clamp(static_cast<int>(colors.z), MIN_COLOR_VALUE, MAX_COLOR_VALUE), 
                static_cast<int>(MAX_COLOR_VALUE)
            );
            
            *pixel32 = pixelColor;
        }

        template<typename T1, typename T2>
        void drawBox(Tvec2<T1> min, Tvec2<T1> max, Tvec3<T2> colors) {        
            int minX = std::clamp(static_cast<int>(std::min(min.x, max.x)), 0, static_cast<int>(this->width-1));
            int maxX = std::clamp(static_cast<int>(std::max(min.x, max.x)), 0, static_cast<int>(this->width-1));
            int minY = std::clamp(static_cast<int>(std::min(min.y, max.y)), 0, static_cast<int>(this->height-1));
            int maxY = std::clamp(static_cast<int>(std::max(min.y, max.y)), 0, static_cast<int>(this->height-1));
            ivec3 clampedColor = ivec3(
                std::clamp(static_cast<int>(colors.x), MIN_COLOR_VALUE, static_cast<int>(MAX_COLOR_VALUE)),
                std::clamp(static_cast<int>(colors.y), MIN_COLOR_VALUE, static_cast<int>(MAX_COLOR_VALUE)),
                std::clamp(static_cast<int>(colors.z), MIN_COLOR_VALUE, static_cast<int>(MAX_COLOR_VALUE))
            );

            for (int i = minX; i <= maxX; ++i) {
                for (int j = minY; j <= maxY; ++j) {
                    this->colorOnePixel(ivec2{i,j}, clampedColor);
                }
            }
        }

};

#endif