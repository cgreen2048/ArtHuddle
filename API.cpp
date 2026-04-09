#include "API.hpp"
#include "Global.hpp"

void initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        exit(1);
    }
    createWindow();
    createScreen();
    createRootLayout();
    setEventSystem();
}

void loadSound(std::string filePath) {
    soundPlayer->loadSound(filePath);
}

void playSound(std::string filePath, int loop) {
    soundPlayer->playSound(filePath, loop);
}

void drawTempElement(int type, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color) {
    tempLayout->clearElements();
    guiElement ge = static_cast<guiElement>(type);
    ElementParameters ep;
    ep.point1 = point1;
    ep.point2 = point2;
    ep.point3 = point3;
    ep.color = color;
    ep.point1Type = TagType::IVec;
    ep.point2Type = TagType::IVec;
    ep.point3Type = TagType::IVec;
    ep.colorType = TagType::IVec;
    ep.center = point1;
    ep.radiusX = std::abs(point3.x - point1.x);
    ep.radiusY = std::abs(point2.y - point1.y);
    ep.centerType = TagType::IVec;
    switch (ge) {
		case guiElement::LINE: {
			Line* element = dynamic_cast<Line*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
		case guiElement::BOX: {
			Box* element = dynamic_cast<Box*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
		case guiElement::TRIANGLE: {
			Triangle* element = dynamic_cast<Triangle*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
        case guiElement::ELLIPSE: {
            Ellipse* element = dynamic_cast<Ellipse*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
        }
        case guiElement::LAYOUT: {
			Layout* element = dynamic_cast<Layout*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
		case guiElement::BUTTON: {
			Button* element = dynamic_cast<Button*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
        default: {
            return;
        }
	}
}

void drawElement(int type, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color) {
    guiElement ge = static_cast<guiElement>(type);
    ElementParameters ep;
    ep.point1 = point1;
    ep.point2 = point2;
    ep.point3 = point3;
    ep.color = color;
    ep.point1Type = TagType::IVec;
    ep.point2Type = TagType::IVec;
    ep.point3Type = TagType::IVec;
    ep.colorType = TagType::IVec;
    ep.center = point1;
    ep.radiusX = std::abs(point3.x - point1.x);
    ep.radiusY = std::abs(point2.y - point1.y);
    ep.centerType = TagType::IVec;
    switch (ge) {
		case guiElement::POINT: {
			Point* element = dynamic_cast<Point*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
		case guiElement::LINE: {
			Line* element = dynamic_cast<Line*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
		case guiElement::BOX: {
			Box* element = dynamic_cast<Box*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
		case guiElement::TRIANGLE: {
			Triangle* element = dynamic_cast<Triangle*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
        case guiElement::ELLIPSE: {
            Ellipse* element = dynamic_cast<Ellipse*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
        }
        case guiElement::LAYOUT: {
			Layout* element = dynamic_cast<Layout*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
		case guiElement::BUTTON: {
			Button* element = dynamic_cast<Button*>(factory(ge, ep));
            if (element) {
                rootLayout->addElement(element);
            }
            return;
		}
        default: {
            return;
        }
	}
    tempLayout->clearElements();
}

void update() {
    screen->clear(ivec3(255,255,255));
    rootLayout->draw(screen);
    screen->blitTo(SDL_GetWindowSurface(window));
    SDL_UpdateWindowSurface(window);
    // eventSystem.processEvents(layout);
}

void closeAll() {
    delete soundPlayer;
    delete screen;
    SDL_Quit();
}