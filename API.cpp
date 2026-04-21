#include "API.hpp"
#include "Global.hpp"

Layout* initialize() {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        exit(1);
    }
    createWindow();
    createScreen();
    Layout* layout = createRootLayout();
    setEventSystem();
    SDL_StartTextInput(window);
    return layout;
}

void loadSound(std::string filePath) {
    soundPlayer->loadSound(filePath);
}

void playSound(std::string filePath, int loop) {
    soundPlayer->playSound(filePath, loop);
}

void drawTempElement(int type, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color) {
    clicked(ivec2(-1, -1));
    tempLayout->clearElements();
    guiElement ge = static_cast<guiElement>(type);
    ElementParameters ep;
    ep.color = color;
    ep.colorType = TagType::IVec;
    
    switch (ge) {
		case guiElement::LINE: {
            ep.start = point1;
            ep.end = point2;
            ep.startType = TagType::IVec;
            ep.endType = TagType::IVec;
			Line* element = dynamic_cast<Line*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
		case guiElement::BOX: {
            ep.min = point1;
            ep.max = point2;
            ep.minType = TagType::IVec;
            ep.maxType = TagType::IVec;
			Box* element = dynamic_cast<Box*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
		case guiElement::TRIANGLE: {
            ep.pointA = point1;
            ep.pointB = point2;
            ep.pointC = point3;
            ep.pointAType = TagType::IVec;
            ep.pointBType = TagType::IVec;
            ep.pointCType = TagType::IVec;
			Triangle* element = dynamic_cast<Triangle*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
		}
        case guiElement::ELLIPSE: {
            ep.center = point1;
            ep.radiusX = std::abs(point3.x - point1.x);
            ep.radiusY = std::abs(point2.y - point1.y);
            ep.centerType = TagType::IVec;
            Ellipse* element = dynamic_cast<Ellipse*>(factory(ge, ep));
            if (element) {
                tempLayout->addElement(element);
            }
            return;
        }
        case guiElement::ARROW: {
            if ((point1.x > point2.x) && (point1.y > point2.y)) {
                ivec2 holder = point1;
                point1 = point2;
                point2 = holder;
            }
            ep.min = point1;
            ep.max = point2;            
            ivec2 center = ivec2(std::abs(point2.x + point1.x)/2, std::abs(point2.y + point1.y)/2);

            if ((point3.y > center.y) && (point3.x < point2.x) && (point3.x > point1.x)) {
                ep.pointA = ivec2(point1.x - ((point2.x - point1.x)/5), point2.y);
                ep.pointB = ivec2(point2.x + ((point2.x - point1.x)/5), point2.y);
            }
            else if ((point3.y < center.y) && (point3.x > point1.x) && (point3.x < point2.x)) {
                ep.pointA = ivec2(point1.x - ((point2.x - point1.x)/5), point1.y);
                ep.pointB = ivec2(point2.x + ((point2.x - point1.x)/5), point1.y);
            }
            else if (point3.x < center.x) {
                ep.pointA = ivec2(point1.x, point1.y - ((point2.y - point1.y)/5));
                ep.pointB = ivec2(point1.x, point2.y + ((point2.y - point1.y)/5));
            }
            else {
                ep.pointA = ivec2(point2.x, point1.y - ((point2.y - point1.y)/5));
                ep.pointB = ivec2(point2.x, point2.y + ((point2.y - point1.y)/5));
            }
            
            ep.pointC = point3;
            ep.minType = TagType::IVec;
            ep.maxType = TagType::IVec;
            ep.pointAType = TagType::IVec;
            ep.pointBType = TagType::IVec;
            ep.pointCType = TagType::IVec;
            Arrow* element = dynamic_cast<Arrow*>(factory(ge, ep));
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
    clicked(ivec2(-1, -1));
    guiElement ge = static_cast<guiElement>(type);
    ElementParameters ep;
    ep.color = color;
    ep.colorType = TagType::IVec;
    
    switch (ge) {
		case guiElement::POINT: {
			ep.coords = point1;
            ep.coordsType = TagType::IVec;
            Point* element = dynamic_cast<Point*>(factory(ge, ep));
            if (element) {
                canvasLayout->addElement(element);
            }
            break;
		}
        case guiElement::LINE: {
            ep.start = point1;
            ep.end = point2;
            ep.startType = TagType::IVec;
            ep.endType = TagType::IVec;
			Line* element = dynamic_cast<Line*>(factory(ge, ep));
            if (element) {
                canvasLayout->addElement(element);
            }
            break;
		}
		case guiElement::BOX: {
            ep.min = point1;
            ep.max = point2;
            ep.minType = TagType::IVec;
            ep.maxType = TagType::IVec;
			Box* element = dynamic_cast<Box*>(factory(ge, ep));
            if (element) {
                canvasLayout->addElement(element);
            }
            break;
		}
		case guiElement::TRIANGLE: {
            ep.pointA = point1;
            ep.pointB = point2;
            ep.pointC = point3;
            ep.pointAType = TagType::IVec;
            ep.pointBType = TagType::IVec;
            ep.pointCType = TagType::IVec;
			Triangle* element = dynamic_cast<Triangle*>(factory(ge, ep));
            if (element) {
                canvasLayout->addElement(element);
            }
            break;
		}
        case guiElement::ELLIPSE: {
            ep.center = point1;
            ep.radiusX = std::abs(point3.x - point1.x);
            ep.radiusY = std::abs(point2.y - point1.y);
            ep.centerType = TagType::IVec;
            Ellipse* element = dynamic_cast<Ellipse*>(factory(ge, ep));
            if (element) {
                canvasLayout->addElement(element);
            }
            break;
        }
        case guiElement::ARROW: {
            if ((point1.x > point2.x) && (point1.y > point2.y)) {
                ivec2 holder = point1;
                point1 = point2;
                point2 = holder;
            }
            ep.min = point1;
            ep.max = point2;    
            ivec2 center = ivec2(std::abs(point2.x + point1.x)/2, std::abs(point2.y + point1.y)/2);

            if ((point3.y > center.y) && (point3.x < point2.x) && (point3.x > point1.x)) {
                ep.pointA = ivec2(point1.x - ((point2.x - point1.x)/5), point2.y);
                ep.pointB = ivec2(point2.x + ((point2.x - point1.x)/5), point2.y);
            }
            else if ((point3.y < center.y) && (point3.x > point1.x) && (point3.x < point2.x)) {
                ep.pointA = ivec2(point1.x - ((point2.x - point1.x)/5), point1.y);
                ep.pointB = ivec2(point2.x + ((point2.x - point1.x)/5), point1.y);
            }
            else if (point3.x < center.x) {
                ep.pointA = ivec2(point1.x, point1.y - ((point2.y - point1.y)/5));
                ep.pointB = ivec2(point1.x, point2.y + ((point2.y - point1.y)/5));
            }
            else {
                ep.pointA = ivec2(point2.x, point1.y - ((point2.y - point1.y)/5));
                ep.pointB = ivec2(point2.x, point2.y + ((point2.y - point1.y)/5));
            }
            
            ep.pointC = point3;
            ep.minType = TagType::IVec;
            ep.maxType = TagType::IVec;
            ep.pointAType = TagType::IVec;
            ep.pointBType = TagType::IVec;
            ep.pointCType = TagType::IVec;
            Arrow* element = dynamic_cast<Arrow*>(factory(ge, ep));
            if (element) {
                canvasLayout->addElement(element);
            }
            break;
        }
        case guiElement::TEXTBOX: {
            if (point1.x > point2.x) {
                ivec2 holder = point1;
                point1 = point2;
                point2 = holder;
            }
            ep.min = point1;
            ep.max = point2;
            ep.color = ivec3(220, 220, 220);
            ep.textColor = color;
            ep.text = "";
            TextBox* element = dynamic_cast<TextBox*>(factory(guiElement::TEXTBOX, ep));
            if (element) {
                canvasLayout->addElement(element);
            }
            break;
        }
        default: {
            break;
        }
	}
    tempLayout->clearElements();
}

void drawToolBar(){
    toolBarLayout->addElement(selectButton);
    toolBarLayout->addElement(pointButton);
    toolBarLayout->addElement(lineButton);
    toolBarLayout->addElement(boxButton);
    toolBarLayout->addElement(triangleButton);
    toolBarLayout->addElement(ellipseButton);
    toolBarLayout->addElement(arrowButton);
    toolBarLayout->addElement(textBoxButton);
    toolBarLayout->addElement(freehandLineButton);
    toolBarLayout->addElement(freehandShapeButton);
}

void clicked(ivec2 coords) {
    EventSystem& eventSystem = EventSystem::getInstance();
    eventSystem.push(std::make_unique<ClickEvent>(coords.x, coords.y));
}

bool isSelectedTextBox() {
    GuiElement* element = Selected::getInstance().getSelectedElement();
    if (dynamic_cast<TextBox*>(element)) {
        return true;
    }
    return false;
}

void appendToTextBox(const std::string& s) {
    GuiElement* element = Selected::getInstance().getSelectedElement();
    TextBox* textbox = dynamic_cast<TextBox*>(element);
    textbox->appendText(s);
}

void deleteText() {
    GuiElement* element = Selected::getInstance().getSelectedElement();
    TextBox* textbox = dynamic_cast<TextBox*>(element);
    if (textbox->getText().empty()) {
        deleteShape();
        return;
    }
    textbox->backspace();
}

void deleteShape() {
    GuiElement* element = Selected::getInstance().getSelectedElement();
    if (element != nullptr) {
        canvasLayout->deleteElement(element->getName());
    }
    tempLayout->clearElements();
}

void update() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    screen->clear(ivec3(255,255,255));
    EventSystem& eventSystem = EventSystem::getInstance();
    eventSystem.processEvents(rootLayout);
    rootLayout->draw(screen);
    // tempLayout->draw(screen);
    // screen->blitTo(SDL_GetWindowSurface(window));
    // SDL_UpdateWindowSurface(window);
    
    screen->renderToRenderer();
    rootLayout->drawOverlay(screen);
    SDL_RenderPresent(renderer);
}

void closeAll() {
    delete soundPlayer;
    delete screen;
    SDL_StopTextInput(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

