#include <iostream>
#include <SDL3/SDL.h>
#include "../Screen.hpp"
#include "../vec2.hpp"
#include "../vec3.hpp"

// unit tests for screen class

const int X = 960;
const int Y = 540;

int screenTest(Screen, SDL_Window*);
int drawBoxTest(Screen, SDL_Window*);
int drawBresenhamLineTest(Screen, SDL_Window*);
int colorOnePixelTest(Screen, SDL_Window*);
int blitToTest(Screen, SDL_Window*);

int main(int argc, char** argv) {
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
		return -1;
	}
    
    Screen screen = Screen(X, Y);
	SDL_Window *window = SDL_CreateWindow("Hello Window", X, Y, 0);

	// screenTest(screen, window);
    int box = drawBoxTest(screen, window);
    int line = drawBresenhamLineTest(screen, window);
    int pixel = colorOnePixelTest(screen, window);
    int blit = blitToTest(screen, window);

    int failure = 0;
    if (box || line || pixel || blit) failure = 1;

	SDL_Quit();
	return failure;
}


int screenTest(Screen screen, SDL_Window *window) {
	bool end = false;
	SDL_Event event;
	while (!end) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT: end = true; break;
			}
		}

		// screen.drawBox(ivec2(X/4, Y/4), ivec2((3*X)/4, (3*Y)/4), ivec3(160, 75, 27));
		screen.drawBox(ivec2((3*X)/4, (3*Y)/4), ivec2(X/4, Y/4), ivec3(160, 75, 27));
		screen.drawBresenhamLine(ivec2(X/2, Y/2), ivec2(0, 0), ivec3(90, 150, 50));
		screen.drawBresenhamLine(ivec2(X/2, Y/2), ivec2(X - 1, 0), ivec3(90, 150, 50));
		screen.drawBresenhamLine(ivec2(X/2, Y/2), ivec2(0, Y - 1), ivec3(90, 150, 50));
		screen.drawBresenhamLine(ivec2(X/2, Y/2), ivec2(X - 1, Y - 1), ivec3(90, 150, 50));

		screen.blitTo(SDL_GetWindowSurface(window));
		SDL_UpdateWindowSurface(window);
	}

	return 0;
}

int drawBoxTest(Screen screen, SDL_Window *window) {
    std::cout << "Testing drawBox function\n";
    int failure = 0;
    
    screen.drawBox(ivec2((3*X)/4, (3*Y)/4), ivec2(X/4, Y/4), ivec3(160, 75, 27));
    screen.drawBox(ivec2(-X, -Y), ivec2(X*2, Y*2), ivec3(-34, 276, 0));
    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_MOUSE_BUTTON_DOWN: 
                    quit = true;
                    break;
			}
		}
    }

    return failure;
}

int drawBresenhamLineTest(Screen screen, SDL_Window *window) {
    std::cout << "Testing drawBresenhamLine function\n";
    int failure = 0;
    
    screen.drawBresenhamLine(ivec2((3*X)/4, (3*Y)/4), ivec2(X/4, Y/4), ivec3(160, 75, 27));
    screen.drawBresenhamLine(ivec2(-X, -Y), ivec2(X*2, Y*2), ivec3(-34, 276, 0));
    screen.drawBresenhamLine(ivec2(0, 0), ivec2(X*2, Y*2), ivec3(-34, 276, 0));
    screen.drawBresenhamLine(ivec2(0, 0), ivec2(X/2, Y/2), ivec3(-34, 276, 0));
    screen.blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_MOUSE_BUTTON_DOWN: 
                    quit = true;
                    break;
			}
		}
    }

    return failure;
}

int colorOnePixelTest(Screen screen, SDL_Window *window) {
    std::cout << "Testing colorOnePixel function\n";
    int failure = 0;
    
    // tests go here
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_MOUSE_BUTTON_DOWN: 
                    quit = true;
                    break;
			}
		}
    }

    return failure;
}

int blitToTest(Screen screen, SDL_Window *window) {
    std::cout << "Testing blitTo function\n";
    int failure = 0;
    
    // tests go here
    SDL_UpdateWindowSurface(window);

    bool quit = false;
    SDL_Event event;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_MOUSE_BUTTON_DOWN: 
                    quit = true;
                    break;
			}
		}
    }

    return failure;
}