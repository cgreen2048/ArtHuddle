#include <iostream>
#include <SDL3/SDL.h>
#include "ArtHuddle/elements/Screen.hpp"
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"

// Unit tests for Screen class

const int X = 960;
const int Y = 540;


int drawBoxTest(Screen, SDL_Window*);
int drawBresenhamLineTest(Screen, SDL_Window*);
int colorOnePixelTest(Screen, SDL_Window*);
int blitToTest(Screen, SDL_Window*);
void getPixelColor(SDL_Surface*, ivec2, uint8_t&, uint8_t&, uint8_t&);

int main(int argc, char** argv) {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
		return -1;
	}
    
    int failure = 0;

    std::cout << "Testing default constructor\n";
    Screen defaultScreen = Screen();
    if (defaultScreen.getWidth() == 0 && defaultScreen.getHeight() == 0 && defaultScreen.getSurface() == nullptr) {
        std::cout << "default constructor working\n";
    }
    else {
        std::cout << "default constructor FAILED!\n";
        failure = 1;
    }

    Screen screen = Screen(X, Y);
    

	SDL_Window *window = SDL_CreateWindow("Hello Window", X, Y, 0);

    int box = drawBoxTest(screen, window);
    if (box) {
        std::cout << "drawBox FAILED\n";
    }
    else {
        std::cout << "drawBox working\n";
    }

    int line = drawBresenhamLineTest(screen, window);
    if (line) {
        std::cout << "drawBresenhamLine FAILED\n";
    }
    else {
        std::cout << "drawBresenhamLine working\n";
    }

    int pixel = colorOnePixelTest(screen, window);
    if (pixel) {
        std::cout << "colorOnePixel FAILED\n";
    }
    else {
        std::cout << "colorOnePixel working\n";
    }

    int blit = blitToTest(screen, window);
    if (blit) {
        std::cout << "blitTo FAILED\n";
    }
    else {
        std::cout << "blitTo working\n";
    }

    if (box || line || pixel || blit) {
        failure = 1;
    }

    std::cout << "Testing copy constructor\n";
    Screen copyScreen{screen};
    if (copyScreen == screen) {
        std::cout << "copy constructor working\n";
    }
    else {
        std::cout << "copy constructor FAILED!\n";
        failure = 1;
    }

    Screen blank = screen;
    if (blank == screen) {
        std::cout << "operator= working\n";
    }
    else {
        std::cout << "operator= FAILED\n";
        failure = 1;
    }

	SDL_Quit();
	return failure;
}

int blitToTest(Screen screen, SDL_Window *window) {
    std::cout << "Testing blitTo function\n";
    int failure = 0;
    
    SDL_Surface* windowScreen = SDL_GetWindowSurface(window);
    screen.blitTo(windowScreen);
    SDL_UpdateWindowSurface(window);

    if (!screen.surfaceEqual(windowScreen)) {
        failure = 1;
    }

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    quit = true;
                    break;
                }
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
			}
		}
    }

    return failure;
}

int drawBresenhamLineTest(Screen screen, SDL_Window *window) {
    std::cout << "Testing drawBresenhamLine function\n";
    int failure = 0;
    
    uint8_t r1,g1,b1,r2,g2,b2;

    screen.drawBresenhamLine(ivec2((3*X)/4, (3*Y)/4), ivec2(X/4, Y/4), ivec3(160, 75, 27), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));
    getPixelColor(screen.getSurface(), ivec2((3*X)/4, (3*Y)/4), r1, g1, b1);
    getPixelColor(screen.getSurface(), ivec2(X/4, Y/4), r2, g2, b2);
    if (r1 != 160 || g1 != 75 || b1 != 27 || r2 != 160 || g2 != 75 || b2 != 27) {
        failure = 1;
    }

    screen.drawBresenhamLine(ivec2(-X, -Y), ivec2(X*2, Y*2), ivec3(-34, 276, 0), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));
    getPixelColor(screen.getSurface(), ivec2(0,0), r1,g1,b1);
    getPixelColor(screen.getSurface(), ivec2(X-1, Y-1), r2,g2,b2);
    if (r1 != 0 || g1 != 255 || b1 != 0 || r2 != 0 || g2 != 255 || b2 != 0) {
        failure = 1;
    }

    screen.drawBresenhamLine(ivec2(0, Y-1), ivec2(X*2, 0), ivec3(-34, 276, 0), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));
    getPixelColor(screen.getSurface(), ivec2(0,Y-1), r1,g1,b1);
    getPixelColor(screen.getSurface(), ivec2(X-1, Y/2), r2,g2,b2);
    if (r1 != 0 || g1 != 255 || b1 != 0 || r2 != 0 || g2 != 255 || b2 != 0) {  
        failure = 1;
    }

    screen.drawBresenhamLine(ivec2(0, Y-1), ivec2(X/2, Y/2), ivec3(-34, 276, 0), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));
    getPixelColor(screen.getSurface(), ivec2(0, Y-1), r1,g1,b1);
    getPixelColor(screen.getSurface(), ivec2(X/2, Y/2), r2,g2,b2);
    if (r1 != 0 || g1 != 255 || b1 != 0 || r2 != 0 || g2 != 255 || b2 != 0) {
        failure = 1;
    }

    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    quit = true;
                    break;
                }
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
			}
		}
    }

    return failure;
}

int colorOnePixelTest(Screen screen, SDL_Window *window) {
    std::cout << "Testing colorOnePixel function\n";
    int failure = 0;
    
    uint8_t r, g, b;

    screen.colorOnePixel(ivec2((3*X)/4, (3*Y)/4), ivec3(160, 75, 27), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));
    getPixelColor(screen.getSurface(), ivec2((3*X)/4, (3*Y)/4), r, g, b);
    if (r != 160 || g != 75 || b != 27) {
        failure = 1;
    }

    screen.colorOnePixel(ivec2(-X, -Y), ivec3(-34, 276, 0), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));

    screen.colorOnePixel(vec2(0, 0), vec3(-34, 276, 0), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));
    getPixelColor(screen.getSurface(), ivec2(0,0), r, g, b);
    if (r != 0 || g != 255 || b != 0) {
        failure = 1;
    }

    screen.colorOnePixel(ivec2(50, 150), ivec3(-34, 276, 0), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));
    getPixelColor(screen.getSurface(), ivec2(50,150), r, g, b);
    if (r != 0 || g != 255 || b != 0) {
        failure = 1;
    }

    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    quit = true;
                    break;
                }
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
			}
		}
    }

    return failure;
}

int drawBoxTest(Screen screen, SDL_Window *window) {
    std::cout << "Testing drawBox function\n";
    int failure = 0;
    
    int boxXMin = X/4;
    int boxXMax = (3*X)/4;
    int boxYMin = Y/4;
    int boxYMax = (3*Y)/4;
    screen.drawBox(ivec2((3*X)/4, (3*Y)/4), ivec2(X/4, Y/4), ivec3(160, 75, 27), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));
    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

    uint8_t r, g, b;

    for (int i = 0; i < screen.getWidth(); ++i) {
        for (int j = 0; j < screen.getHeight(); ++j) {
            getPixelColor(screen.getSurface(), ivec2(i, j), r, g, b);
            if ((i >= boxXMin) && (i <= boxXMax) && (j >= boxYMin) && (j <= boxYMax)) {
                if (r != 160 || g != 75 || b != 27) {
                    failure = 1;
                    break;
                }
            }
            else {
                if (r != 0 || g != 0 || b != 0) {
                    failure = 1;
                    break;
                }
            }
        }
        if (failure) {
            break;
        } 
    }

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    quit = true;
                    break;
                }
                case SDL_EVENT_QUIT: {
                    quit = true;
                    break;
                }
			}
		}
    }

    return failure;
}

void getPixelColor(SDL_Surface* surface, ivec2 coords, uint8_t& r, uint8_t& g, uint8_t& b) {
    uint8_t* pixelPtr = static_cast<uint8_t*>(surface->pixels);
    uint8_t* pixel = pixelPtr 
        + static_cast<int>(coords.x) * sizeof(uint32_t) 
        + static_cast<int>(coords.y) * surface->pitch;
    uint32_t pixel32 = *reinterpret_cast<uint32_t*>(pixel);
    const SDL_PixelFormatDetails *details =  SDL_GetPixelFormatDetails(surface->format);

    uint8_t a;
    SDL_GetRGBA(pixel32, details, NULL, &r, &g, &b, &a);
}