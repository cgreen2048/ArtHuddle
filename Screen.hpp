#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <iostream>
#include <SDL3/SDL.h>
#include "vec2.h"
#include "vec3.h"
#define ALPHA_VALUE 255

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
        void colorOnePixel(vec2, vec3);
        void blitTo(SDL_Surface*);
        void drawBresenhamLine();
        void drawBox(ivec2, ivec2);
        void drawBox(ivec3, ivec3);
};

#endif