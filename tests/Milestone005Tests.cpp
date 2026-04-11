#include <iostream>
#include <typeinfo>
#include "../Factory.hpp"
#include "../GuiElement.hpp"
#include "../Point.hpp"
#include "../Line.hpp"
#include "../Box.hpp"
#include "../Triangle.hpp"

const int X = 960;
const int Y = 540;

int clearTests(Screen, SDL_Window*);
int boundsTests(Screen, SDL_Window*);
void getPixelColor(SDL_Surface*, ivec2, uint8_t&, uint8_t&, uint8_t&);


int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    int failure = 0;
    Screen screen = Screen(X, Y);
    SDL_Window *window = SDL_CreateWindow("Hello Window", X, Y, 0);
    
    if (clearTests(screen, window)) {
        failure = 1;
    }
    if (boundsTests(screen, window)) {
        failure = 1;
    }
    if (failure) {
        std::cout << "IMPLEMENTATION(S) FAILED, REVIEW TESTS\n";
    }
    else {
        std::cout << "all tests passed\n";
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return failure;
}


int clearTests(Screen screen, SDL_Window* window) {
    int failure = 0;
    std::cout << "Testing clear function\n";

    uint8_t r, g, b;

    // Draw something first
    screen.drawBox(ivec2(10, 10), ivec2(100, 100), ivec3(200, 50, 25), ivec2(0, 0), ivec2(screen.getWidth(), screen.getHeight()));

    // Confirm shape pixel was drawn correctly
    getPixelColor(screen.getSurface(), ivec2(50, 50), r, g, b);
    if (r != 200 || g != 50 || b != 25) {
        std::cout << "clear test setup FAILED\n";
        failure = 1;
    }

    // Clear the screen
    screen.clear(ivec3(255, 255, 255));

    // Check formerly colored pixel
    getPixelColor(screen.getSurface(), ivec2(50, 50), r, g, b);
    if (r != 255 || g != 255 || b != 255) {
        std::cout << "clear FAILED at overwritten pixel\n";
        failure = 1;
    }

    // Check some other pixel too
    getPixelColor(screen.getSurface(), ivec2(500, 300), r, g, b);
    if (r != 255 || g != 255 || b != 255) {
        std::cout << "clear FAILED at general surface pixel\n";
        failure = 1;
    }

    if (failure) {
        std::cout << "clear tests FAILED\n";
    }
    else {
        std::cout << "clear tests passed\n";
    }

    return failure;
}

int boundsTests(Screen screen, SDL_Window* window) {
    int failure = 0;

    GuiElement *triangle = new Triangle(ivec2(50,50), ivec2(120,200), ivec2(100, 50), ivec3(100,100,100));
    triangle->setParentStart(ivec2(0, 0));
    triangle->setParentEnd(ivec2(150, 140));

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
            screen.clear(ivec3(255,255,255));
            triangle->draw(&screen);
            screen.blitTo(SDL_GetWindowSurface(window));
            SDL_UpdateWindowSurface(window);
		}
    }

    GuiElement *box = new Box(ivec2(50,50), ivec2(120,200), ivec3(100,100,100));
    box->setParentStart(ivec2(0, 0));
    box->setParentEnd(ivec2(150, 100));
    quit = 0;
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
            screen.clear(ivec3(255,255,255));
            box->draw(&screen);
            screen.blitTo(SDL_GetWindowSurface(window));
            SDL_UpdateWindowSurface(window);
		}
    }

    GuiElement *line = new Line(ivec2(50,50), ivec2(120,200), ivec3(100,100,100));
    line->setParentStart(ivec2(0, 0));
    line->setParentEnd(ivec2(60, 60));
    quit = 0;
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
            screen.clear(ivec3(255,255,255));
            line->draw(&screen);
            screen.blitTo(SDL_GetWindowSurface(window));
            SDL_UpdateWindowSurface(window);
		}
    }

    GuiElement *point = new Point(ivec2(50,50), ivec3(100,100,100));
    point->setParentStart(ivec2(75, 75));
    point->setParentEnd(ivec2(150, 100));
    quit = 0;
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
            screen.clear(ivec3(255,255,255));
            point->draw(&screen);
            screen.blitTo(SDL_GetWindowSurface(window));
            SDL_UpdateWindowSurface(window);
		}
    }

    if (failure) {
        std::cout << "bounds tests FAILED\n";
    }
    else {
        std::cout << "bounds tests passed\n";
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