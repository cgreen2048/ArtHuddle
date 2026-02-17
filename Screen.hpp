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
        Screen();
        Screen(uint32_t, uint32_t);
        Screen(const Screen&);
        ~Screen();
        Screen& operator=(const Screen&);
        void blitTo(SDL_Surface*) const;
        void drawBresenhamLine(ivec2, ivec2, ivec3);

        template<typename T1, typename T2>
        void colorOnePixel(const Tvec2<T1> coords, const Tvec3<T2> colors) {
            uint8_t* pixelPtr = static_cast<uint8_t*>(surface->pixels);
            uint8_t* pixel = pixelPtr 
                + static_cast<int>(coords.x) * sizeof(uint32_t) 
                + static_cast<int>(coords.y) * surface->pitch;
            uint32_t* pixel32 = reinterpret_cast<uint32_t*>(pixel);
            const SDL_PixelFormatDetails *details =  SDL_GetPixelFormatDetails(surface->format);
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
            int minX = std::clamp(static_cast<int>(std::min(min.x, max.x)), 0, static_cast<int>(width-1));
            int maxX = std::clamp(static_cast<int>(std::max(min.x, max.x)), 0, static_cast<int>(width-1));
            int minY = std::clamp(static_cast<int>(std::min(min.y, max.y)), 0, static_cast<int>(height-1));
            int maxY = std::clamp(static_cast<int>(std::max(min.y, max.y)), 0, static_cast<int>(height-1));

            for (int i = minX; i <= maxX; ++i) {
                for (int j = minY; j <= maxY; ++j) {
                    colorOnePixel(ivec2{i,j}, colors);
                }
            }
        }

};

#endif