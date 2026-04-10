#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <iostream>
#include <algorithm>
#include <SDL3/SDL.h>
#include <cstring>
#include <string>
#include "vec2.hpp"
#include "vec3.hpp"
#define MIN_COLOR_VALUE 0
#define MAX_COLOR_VALUE 255
static constexpr int SDL_DEBUG_FONT_WIDTH = 8;
static constexpr int SDL_DEBUG_FONT_HEIGHT = 8;

class Screen {
    private:
        uint32_t width, height;
        SDL_Surface* surface = nullptr;
        SDL_Renderer* renderer = nullptr;
        
    public:
        Screen();
        Screen(uint32_t w, uint32_t h);
        Screen(const Screen& cp);
        ~Screen();
        Screen& operator=(const Screen& cp);
        bool operator==(const Screen rhs);

        bool surfaceEqual(const SDL_Surface* rhs);
        void blitTo(SDL_Surface* target) const;
        void drawBresenhamLine(ivec2 start, ivec2 end, ivec3 color, ivec2 parentStart, ivec2 parentEnd);
        bool pointInTriangle(ivec2 pointA, ivec2 pointB, ivec2 pointC, ivec2 pointP);
        void drawTriangle(ivec2 pointA, ivec2 pointB, ivec2 pointC, ivec3 colors, ivec2 parentStart, ivec2 parentEnd);
        void clear(ivec3 color);

        SDL_Surface* getSurface();
        uint32_t getWidth();
        uint32_t getHeight();


        template<typename T1, typename T2>
        void colorOnePixel(const Tvec2<T1> coords, const Tvec3<T2> colors, ivec2 parentStart, ivec2 parentEnd) {
            if ((coords.x < 0) || (coords.x > this->width - 1) || (coords.y < 0) || (coords.y > this->height - 1)) {
                // std::cerr << "Point is out of bounds\n";
                return;
            }
            if ((coords.x < parentStart.x) || (coords.x >= parentEnd.x) || (coords.y < parentStart.y) || (coords.y >= parentEnd.y)) {
                // std::cerr << "Point is out of bounds\n";
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
        void drawBox(Tvec2<T1> min, Tvec2<T1> max, Tvec3<T2> colors, ivec2 parentStart, ivec2 parentEnd) {        
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
                    this->colorOnePixel(ivec2{i,j}, clampedColor, parentStart, parentEnd);
                }
            }
        }
        
        template<typename T1, typename T2>
        void drawText(Tvec2<T1> pos, const std::string& text, Tvec3<T2> textColors) {
            if (!renderer || text.empty()) 
            {
                return;
            }

            SDL_Color sdlColor = {
                static_cast<Uint8>(std::clamp(static_cast<int>(textColors.x), MIN_COLOR_VALUE, MAX_COLOR_VALUE)),
                static_cast<Uint8>(std::clamp(static_cast<int>(textColors.y), MIN_COLOR_VALUE, MAX_COLOR_VALUE)),
                static_cast<Uint8>(std::clamp(static_cast<int>(textColors.z), MIN_COLOR_VALUE, MAX_COLOR_VALUE)),
                255
            };

            SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
            SDL_RenderDebugText(renderer, static_cast<float>(pos.x), static_cast<float>(pos.y), text.c_str());
        }


        template<typename T1, typename T2>
        void drawTextCentered(Tvec2<T1> min, Tvec2<T1> max, const std::string& text, Tvec3<T2> textColors) {
            if (text.empty()) 
            {
                return;
            }

            int textWidth = static_cast<int>(text.size()) * SDL_DEBUG_FONT_WIDTH;
            int textHeight = SDL_DEBUG_FONT_HEIGHT;

            int boxWidth = max.x - min.x;
            int boxHeight = max.y - min.y;

            int x = min.x + (boxWidth - textWidth) / 2;
            int y = min.y + (boxHeight - textHeight) / 2;

            drawText(ivec2(x, y), text, textColors);
        }

};

#endif