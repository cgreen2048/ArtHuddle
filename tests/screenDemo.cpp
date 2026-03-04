#include <iostream>
#include <SDL3/SDL.h>
#include "../Screen.hpp"
#include "../vec2.hpp"
#include "../vec3.hpp"

const int X = 960;
const int Y = 540;

void screenDemo(Screen, SDL_Window*);

int main(int argc, char** argv) {
	std::cout << "Screen Class Demonstration\n";

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("Screen Demo", X, Y, 0);
	Screen screen = Screen(X, Y);
	screenDemo(screen, window);

	SDL_Quit();

	std::cout << "SDL opened and closed successfully\n";

	return 0;
}

void screenDemo(Screen screen, SDL_Window *window) {
	bool end = false;
	SDL_Event event;
	while (!end) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT: {
					end = true; 
					break;
				}
			}
		}

		screen.drawBox(ivec2((3*X)/4, (3*Y)/4), ivec2(X/4, Y/4), ivec3(160, 75, 27));
		screen.drawBresenhamLine(ivec2(X/2, Y/2), ivec2(0, 0), ivec3(90, 150, 50));
		screen.drawBresenhamLine(ivec2(X/2, Y/2), ivec2(X - 1, 0), ivec3(90, 150, 50));
		screen.drawBresenhamLine(ivec2(X/2, Y/2), ivec2(0, Y - 1), ivec3(90, 150, 50));
		screen.drawBresenhamLine(ivec2(X/2, Y/2), ivec2(X - 1, Y - 1), ivec3(90, 150, 50));
		screen.drawTriangle(ivec2(X/4, Y/4), ivec2(X/4, Y/2), ivec2((3*X) / 4, Y/3), ivec3(100, 150, 50));
		screen.drawTriangle(ivec2(0, 0), ivec2(0, Y), ivec2(X,Y), ivec3(100, 150, 50));

		screen.blitTo(SDL_GetWindowSurface(window));
		SDL_UpdateWindowSurface(window);
	}

	return;
}