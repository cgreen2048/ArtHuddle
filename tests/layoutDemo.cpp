#include <iostream>
#include <SDL3/SDL.h>
#include "../Factory.hpp"
#include "../Layout.hpp"
#include "../Screen.hpp"
#include "../vec2.hpp"
#include "../vec3.hpp"
#include "../Box.hpp"
#include "../Triangle.hpp"
#include "../GuiElement.hpp"

const int X = 960;
const int Y = 540;

int layoutDemo(Screen*, SDL_Window*);

int main() {
    std::cout << "Layout Class Demo\n";

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Layout Demo", X, Y, 0);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
        return 1;
    }

    Screen *screen = new Screen(X, Y);

    int failure = layoutDemo(screen, window);

    SDL_Quit();

    if (failure == 1) {
        std::cout << "Demo did not execute successfully\n";
    }
    else {
        std::cout << "Demo succeeded and window closed\n";
    }

    return failure;
}

int layoutDemo(Screen* screen, SDL_Window *window) {
    bool end = false;
    int failure = 0;
    SDL_Event event;
    float mouseX, mouseY;
    int x, y;

    Layout* layout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT));
    layout->setScreen(screen);
    layout->setStart(vec2{0.1,0.1});
    layout->setEnd(vec2{1.0, 1.0});
    layout->setParentStart(ivec2{0,0});
    layout->setParentEnd(ivec2{X,Y});


    Triangle* tri = dynamic_cast<Triangle*>(factory(guiElement::TRIANGLE));
    tri->setA(ivec2(100, 100), Triangle::TagType::IVec);
    tri->setB(ivec2(150, 100), Triangle::TagType::IVec);
    tri->setC(ivec2(125, 150), Triangle::TagType::IVec);
    tri->setColor(ivec3(255, 0, 0), Triangle::TagType::IVec);
    layout->addElement(tri);

    Box* b = dynamic_cast<Box*>(factory(guiElement::BOX));
    b->setMin(ivec2(200,200), Box::TagType::IVec);
    b->setMax(ivec2(400,400), Box::TagType::IVec);
    b->setColor(ivec3(0, 255, 255), Box::TagType::IVec);
    layout->addElement(b);

    Layout* nestedLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT));
    nestedLayout->setStart(vec2{0.5, 0.5});
    nestedLayout->setEnd(vec2{1.0, 1.0});
    layout->addElement(nestedLayout);

    Line* nestedLayoutVerticalBorder = dynamic_cast<Line*>(factory(guiElement::LINE));
    nestedLayoutVerticalBorder->setStart(ivec2(X/2, Y/2), Line::TagType::IVec);
    nestedLayoutVerticalBorder->setEnd(ivec2(X/2, Y), Line::TagType::IVec);
    nestedLayoutVerticalBorder->setColor(ivec3(0, 0, 0), Line::TagType::IVec);
    nestedLayout->addElement(nestedLayoutVerticalBorder);

    Line* nestedLayoutHorizontalBorder = dynamic_cast<Line*>(factory(guiElement::LINE));
    nestedLayoutHorizontalBorder->setStart(ivec2(X/2, Y/2), Line::TagType::IVec);
    nestedLayoutHorizontalBorder->setEnd(ivec2(X, Y/2), Line::TagType::IVec);
    nestedLayoutHorizontalBorder->setColor(ivec3(0, 0, 0), Line::TagType::IVec);
    nestedLayout->addElement(nestedLayoutHorizontalBorder);

    Box* nestedBox = dynamic_cast<Box*>(factory(guiElement::BOX));
    nestedBox->setMin(ivec2(800,200), Box::TagType::IVec);      // intentionally cut off the top end of the box to show relative pos
    nestedBox->setMax(ivec2(900,500), Box::TagType::IVec);
    nestedBox->setColor(ivec3(255, 0, 0), Box::TagType::IVec);
    nestedLayout->addElement(nestedBox);

    Triangle* nestedTri = dynamic_cast<Triangle*>(factory(guiElement::TRIANGLE));
    nestedTri->setA(ivec2(500, 530), Triangle::TagType::IVec);
    nestedTri->setB(ivec2(750, 510), Triangle::TagType::IVec);
    nestedTri->setC(ivec2(600, 460), Triangle::TagType::IVec);
    nestedTri->setColor(ivec3(255, 0, 255), Triangle::TagType::IVec);
    nestedLayout->addElement(nestedTri);

    Line* nestedLine = dynamic_cast<Line*>(factory(guiElement::LINE));
    nestedLine->setStart(ivec2(480, 280), Line::TagType::IVec);
    nestedLine->setEnd(ivec2(940, 530), Line::TagType::IVec);
    nestedLine->setColor(ivec3(132, 231, 52), Line::TagType::IVec);
    nestedLayout->addElement(nestedLine);

    layout->setActive(true);

    while (!end) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    end = true;
                    break;
                }
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);
        x = static_cast<int>(mouseX);
        y = static_cast<int>(mouseY);
        bool inside = screen->pointInTriangle(tri->getA(), tri->getB(), tri->getC(), ivec2(x, y));
        std::cout << inside << '\n';
        if (inside) {
            nestedLayout->setActive(true);
        }
        else {
            nestedLayout->setActive(false);
        }

        screen->clear(ivec3(255,255,255));

        layout->draw();
        screen->blitTo(SDL_GetWindowSurface(window));
		SDL_UpdateWindowSurface(window);
    }
    delete layout;

    return failure;
}