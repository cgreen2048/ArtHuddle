#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <iostream>
#include <algorithm>
#include <SDL3/SDL.h>
#include "vec2.hpp"
#include "vec3.hpp"
#define MAX_COLOR_VALUE 255

class Screen {
    private:
        uint32_t width, height;
        SDL_Surface* surface = nullptr;
        
    public:
        void clearSurface();
        Screen();
        Screen(uint32_t, uint32_t);
        Screen(const Screen&);
        ~Screen();
        Screen& operator=(const Screen&);
        void blitTo(SDL_Surface*) const;
        void drawBresenhamLine(ivec2, ivec2, ivec3);

        template<typename T1, typename T2>
        void colorOnePixel(const Tvec2<T1> coords, const Tvec3<T2> colors) {
            if ((coords.x < 0) || (coords.x > this->width - 1) || (coords.y < 0) || (coords.y > this->height - 1)) {
                std::cerr << "Point is out of bounds\n";
                return;
            }
            if ((colors.x < 0) || (colors.x > 255) || (colors.y < 0) || (colors.y > 255) || (colors.z < 0) || (colors.z > 255)) {
                std::cerr << "Invalid color value\n";
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
                std::clamp(static_cast<int>(colors.x), 0, MAX_COLOR_VALUE), 
                std::clamp(static_cast<int>(colors.y), 0, MAX_COLOR_VALUE), 
                std::clamp(static_cast<int>(colors.z), 0, MAX_COLOR_VALUE), 
                static_cast<int>(MAX_COLOR_VALUE)
            );
            
            *pixel32 = pixelColor;
        }

        template<typename T1, typename T2, typename T3>
        void drawBox(Tvec2<T1> min, Tvec2<T2> max, Tvec3<T3> colors) {
            // if ((min.x < 0) || (min.x > this->width - 1) || (min.y < 0) || (min.y > this->height - 1)) {
            //     std::cerr << "Box minimum is out of bounds\n";
            //     return;
            // }
            // if ((max.x < 0) || (max.x > this->width - 1) || (max.y < 0) || (max.y > this->height - 1)) {
            //     std::cerr << "Box maximum is out of bounds\n";
            //     return;
            // }
            if ((colors.x < 0) || (colors.x > 255) || (colors.y < 0) || (colors.y > 255) || (colors.z < 0) || (colors.z > 255)) {
                std::cerr << "Invalid color value\n";
                return;
            }
            
            int minX = std::clamp(static_cast<int>(std::min(min.x, max.x)), 0, static_cast<int>(this->width-1));
            int maxX = std::clamp(static_cast<int>(std::max(min.x, max.x)), 0, static_cast<int>(this->width-1));
            int minY = std::clamp(static_cast<int>(std::min(min.y, max.y)), 0, static_cast<int>(this->height-1));
            int maxY = std::clamp(static_cast<int>(std::max(min.y, max.y)), 0, static_cast<int>(this->height-1));

            for (int i = minX; i <= maxX; ++i) {
                for (int j = minY; j <= maxY; ++j) {
                    this->colorOnePixel(ivec2{i,j}, colors);
                }
            }
        }

};

#endif