#include "API.hpp"
#include "Global.hpp"

Layout* initialize(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3) {
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        std::cerr << "Failed to init SDL3 " << SDL_GetError() << '\n';
        exit(1);
    }
    #ifdef __APPLE__
        SDL_SetHint(SDL_HINT_MAC_PRESS_AND_HOLD, "0");
    #endif
    createWindow();
    createScreen();
    setEventSystem();
    Layout* layout = createRootLayout(mode, points, point1, point2, point3);
    SDL_StartTextInput(window);
    return layout;
}

void loadSound(std::string filePath) {
    soundPlayer->loadSound(filePath);
}

void playSound(std::string filePath, int loop) {
    soundPlayer->playSound(filePath, loop);
}

void drawTempElement(guiElement ge, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color) {
    GuiElement* lastEl = tempLayout->popLast();
    ElementParameters ep;
    ep.color = color;
    ep.colorType = TagType::IVec;
    
    switch (ge) {
		case guiElement::LINE: {
            Line* derived = dynamic_cast<Line*>(lastEl);
            if (derived) {
                derived->setEnd(point2, TagType::IVec);
                derived->setColor(color, TagType::IVec);
                tempLayout->addElement(derived);
            }
            else {
                ep.start = point1;
                ep.end = point2;
                ep.startType = TagType::IVec;
                ep.endType = TagType::IVec;
                Line* element = dynamic_cast<Line*>(factory(ge, ep));
                if (element) {
                    tempLayout->addElement(element);
                }
            }
            return;
		}
		case guiElement::BOX: {
            Box* derived = dynamic_cast<Box*>(lastEl);
            if (derived) {
                derived->setMax(point2, TagType::IVec);
                derived->setColor(color, TagType::IVec);
                tempLayout->addElement(derived);
            }
            else {
                ep.min = point1;
                ep.max = point2;
                ep.minType = TagType::IVec;
                ep.maxType = TagType::IVec;
                Box* element = dynamic_cast<Box*>(factory(ge, ep));
                if (element) {
                    tempLayout->addElement(element);
                }
            }
            return;
		}
		case guiElement::TRIANGLE: {
            Triangle* derived = dynamic_cast<Triangle*>(lastEl);
            if (derived) {
                derived->setC(point3, TagType::IVec);
                derived->setColor(color, TagType::IVec);
                tempLayout->addElement(derived);
            }
            else {
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
            }
            return;
		}
        case guiElement::ELLIPSE: {
            Ellipse* derived = dynamic_cast<Ellipse*>(lastEl);
            if (derived) {
                derived->setRadiusX(point3.x - derived->getCenter().x);
                derived->setColor(color, TagType::IVec);
                tempLayout->addElement(derived);
            }
            else {
                ep.center = point1;
                ep.radiusX = std::abs(point3.x - point1.x);
                ep.radiusY = std::abs(point2.y - point1.y);
                ep.centerType = TagType::IVec;
                Ellipse* element = dynamic_cast<Ellipse*>(factory(ge, ep));
                if (element) {
                    tempLayout->addElement(element);
                }
            }
            return;
        }
        case guiElement::TEXTBOX: {
            TextBox* derived = dynamic_cast<TextBox*>(lastEl);
            if (derived) {
                derived->setMax(point2, TagType::IVec);
                derived->setColor(color, TagType::IVec);
                tempLayout->addElement(derived);
            }
            else {
                ep.min = point1;
                ep.max = point2;
                ep.minType = TagType::IVec;
                ep.maxType = TagType::IVec;
                TextBox* element = dynamic_cast<TextBox*>(factory(ge, ep));
                if (element) {
                    tempLayout->addElement(element);
                }
            }
            return;
		}
        case guiElement::ARROW: {
            ivec2 newMin;
            ivec2 newMax;
            newMin.x = std::min(point1.x, point2.x);
            newMin.y = std::min(point1.y, point2.y);
            newMax.x = std::max(point1.x, point2.x);
            newMax.y = std::max(point1.y, point2.y);
            point1 = newMin;
            point2 = newMax;
            ivec2 A;
            ivec2 B;
            ivec2 center = ivec2(std::abs(point2.x + point1.x)/2, std::abs(point2.y + point1.y)/2);
            if ((point3.y > center.y) && (point3.x < point2.x) && (point3.x > point1.x)) {
                    A = ivec2(point1.x - ((point2.x - point1.x)/5), point2.y);
                    B = ivec2(point2.x + ((point2.x - point1.x)/5), point2.y);
                }
                else if ((point3.y < center.y) && (point3.x > point1.x) && (point3.x < point2.x)) {
                    A = ivec2(point1.x - ((point2.x - point1.x)/5), point1.y);
                    B = ivec2(point2.x + ((point2.x - point1.x)/5), point1.y);
                }
                else if (point3.x < center.x) {
                    A = ivec2(point1.x, point1.y - ((point2.y - point1.y)/5));
                    B = ivec2(point1.x, point2.y + ((point2.y - point1.y)/5));
                }
                else {
                    A = ivec2(point2.x, point1.y - ((point2.y - point1.y)/5));
                    B = ivec2(point2.x, point2.y + ((point2.y - point1.y)/5));
                }
            Arrow* derived = dynamic_cast<Arrow*>(lastEl);
            if (derived) {
                derived->setA(A, TagType::IVec);
                derived->setB(B, TagType::IVec);
                derived->setC(point3, TagType::IVec);
                derived->setColor(color, TagType::IVec);
                tempLayout->addElement(derived);
            }
            else {
                ep.min = point1;
                ep.max = point2;
                ep.pointA = A;
                ep.pointB = B;
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
            }
            return;
        }
        default: {
            return;
        }
	}
}

void drawElement(guiElement ge, ivec2 point1, ivec2 point2, ivec2 point3, ivec3 color) {
    GuiElement* lastEl = tempLayout->popLast();
    if (!lastEl && ge != guiElement::POINT) {
        return;
    }

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
                Selected::getInstance().setSelectedElement(element);
            }
            break;
		}
        case guiElement::LINE: {
            Line* derived = dynamic_cast<Line*>(lastEl);
            if (derived) {
                canvasLayout->addElement(derived);
                Selected::getInstance().setSelectedElement(derived);
            }
            break;
		}
		case guiElement::BOX: {
            Box* derived = dynamic_cast<Box*>(lastEl);
            if (derived) {
                canvasLayout->addElement(derived);
                Selected::getInstance().setSelectedElement(derived);
            }
            break;
		}
		case guiElement::TRIANGLE: {
            Triangle* derived = dynamic_cast<Triangle*>(lastEl);
            if (derived) {
                canvasLayout->addElement(derived);
                Selected::getInstance().setSelectedElement(derived);
            }
            break;
		}
        case guiElement::ELLIPSE: {
            Ellipse* derived = dynamic_cast<Ellipse*>(lastEl);
            if (derived) {
                canvasLayout->addElement(derived);
                Selected::getInstance().setSelectedElement(derived);
            }
            break;
        }
        case guiElement::ARROW: {
            Arrow* derived = dynamic_cast<Arrow*>(lastEl);
            if (derived) {
                canvasLayout->addElement(derived);
                Selected::getInstance().setSelectedElement(derived);
            }
            break;
        }
        case guiElement::TEXTBOX: {
            Box* derived = dynamic_cast<Box*>(lastEl);
            if (derived) {
                ElementParameters textParam = derived->getParameters();
                textParam.textColor = textParam.color;
                textParam.color = ivec3(220, 220, 220);
                textParam.text = "";
                TextBox* element = dynamic_cast<TextBox*>(factory(guiElement::TEXTBOX, textParam));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                delete derived;
            }
            break;
        }
        default: {
            break;
        }
	}
}

void startFreehandDraw(const ivec2& point, const ivec3& color, bool isFreehandShape) {
    ivec2 toolBarBounds = toolBarLayout->getBounds()[1];
    if (point.y < toolBarBounds.y) {
        return;
    }
    Freehand* freehand = new Freehand(color, isFreehandShape);
    canvasLayout->addElement(freehand);
    EventSystem& eventSystem = EventSystem::getInstance();
    eventSystem.setTargetedElement(freehand);
    eventSystem.push(std::make_unique<MouseDownEvent>(point));
}

void continueFreehandDraw(const ivec2& point) {
    ivec2 toolBarBounds = toolBarLayout->getBounds()[1];
    if (point.y < toolBarBounds.y) {
        EventSystem::getInstance().push(std::make_unique<MouseUpEvent>(point));
        return;
    }
    EventSystem::getInstance().push(std::make_unique<MouseMotionEvent>(point, true));
}

void endFreehandDraw(const ivec2& point) {
    EventSystem& eventSystem = EventSystem::getInstance();
    Selected::getInstance().setSelectedElement(eventSystem.getTargetedElement());
    eventSystem.push(std::make_unique<MouseUpEvent>(point));
}

void setClickAndDrag(ivec2 mouse) {
    Selected& selected = Selected::getInstance();
    GuiElement* current = selected.getSelectedElement();
    if (!current || !selected.isInside(mouse)) {
        return;
    }
    lastMousePos = mouse;
    if (draggingElement == nullptr) {
        draggingElement = current;
        if (draggingElement) {
            originalElementParameters = draggingElement->getParameters();
            draggingElementParameters = draggingElement->getParameters();
            draggingType = draggingElement->getType();
            deleteShape();
            drawClickAndDrag(lastMousePos);
            Selected::getInstance().setSelectedElement(nullptr);
        }
    }
}

void endClickAndDrag() {
    if (draggingType != guiElement::UNKNOWN) {
        deleteTempShape();
        ivec2 toolBarBounds = toolBarLayout->getBounds()[1];
        switch (draggingType) {
            case guiElement::POINT: {
                Point* element = dynamic_cast<Point*>(factory(draggingType, draggingElementParameters));
                if (element) {
                    std::vector<ivec2> bounds = element->getBounds();
                    if (bounds[0].y < toolBarBounds.y) {
                        delete element;
                        cancelMove();
                        return;
                    }
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::LINE: {
                Line* element = dynamic_cast<Line*>(factory(draggingType, draggingElementParameters));
                if (element) {
                    std::vector<ivec2> bounds = element->getBounds();
                    if (bounds[0].y < toolBarBounds.y) {
                        delete element;
                        cancelMove();
                        return;
                    }
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::BOX: {
                Box* element = dynamic_cast<Box*>(factory(draggingType, draggingElementParameters));
                if (element) {
                    std::vector<ivec2> bounds = element->getBounds();
                    if (bounds[0].y < toolBarBounds.y) {
                        delete element;
                        cancelMove();
                        return;
                    }
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::TRIANGLE: {
                Triangle* element = dynamic_cast<Triangle*>(factory(draggingType, draggingElementParameters));
                if (element) {
                    std::vector<ivec2> bounds = element->getBounds();
                    if (bounds[0].y < toolBarBounds.y) {
                        delete element;
                        cancelMove();
                        return;
                    }
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::ELLIPSE: {
                Ellipse* element = dynamic_cast<Ellipse*>(factory(draggingType, draggingElementParameters));
                if (element) {
                    std::vector<ivec2> bounds = element->getBounds();
                    if (bounds[0].y < toolBarBounds.y) {
                        delete element;
                        cancelMove();
                        return;
                    }
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::ARROW: {
                Arrow* element = dynamic_cast<Arrow*>(factory(draggingType, draggingElementParameters));
                if (element) {
                    std::vector<ivec2> bounds = element->getBounds();
                    if (bounds[0].y < toolBarBounds.y) {
                        delete element;
                        cancelMove();
                        return;
                    }
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::TEXTBOX: {
                TextBox* element = dynamic_cast<TextBox*>(factory(draggingType, draggingElementParameters));
                if (element) {
                    std::vector<ivec2> bounds = element->getBounds();
                    if (bounds[0].y < toolBarBounds.y) {
                        delete element;
                        cancelMove();
                        return;
                    }
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::FREEHAND: {
                Freehand* element = dynamic_cast<Freehand*>(factory(draggingType, draggingElementParameters));
                if (element) {
                    std::vector<ivec2> bounds = element->getBounds();
                    if (bounds[0].y < toolBarBounds.y) {
                        delete element;
                        cancelMove();
                        return;
                    }
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            default: {
                break;
            }
        }
    }
    draggingElement = nullptr;
    draggingType = guiElement::UNKNOWN;
}

void drawClickAndDrag(ivec2 currentMousePos) {
    if (draggingType != guiElement::UNKNOWN) {
        deleteTempShape();
        Selected::getInstance().setSelectedElement(nullptr);
        ivec2 delta = currentMousePos - lastMousePos;
        draggingElementParameters = originalElementParameters;
        draggingElementParameters.coords += delta;
        draggingElementParameters.start += delta;
        draggingElementParameters.end += delta;
        draggingElementParameters.min += delta;
        draggingElementParameters.max += delta;
        draggingElementParameters.pointA += delta;
        draggingElementParameters.pointB += delta;
        draggingElementParameters.pointC += delta;
        draggingElementParameters.center += delta;
        for (int i = 0; i < draggingElementParameters.points.size(); ++i) {
            draggingElementParameters.points[i] += delta;
        }
        GuiElement* element = factory(draggingType, draggingElementParameters);
        if (element) {
            tempLayout->addElement(element);
        }
    }
}

void cancelMove() {
    deleteTempShape();
    switch (draggingType) {
		case guiElement::POINT: {
            Point* element = dynamic_cast<Point*>(factory(draggingType, originalElementParameters));
            if (element) {
                canvasLayout->addElement(element);
                Selected::getInstance().setSelectedElement(element);
            }
            break;
		}
        case guiElement::LINE: {
			Line* element = dynamic_cast<Line*>(factory(draggingType, originalElementParameters));
            if (element) {
                canvasLayout->addElement(element);
                Selected::getInstance().setSelectedElement(element);
            }
            break;
		}
		case guiElement::BOX: {
			Box* element = dynamic_cast<Box*>(factory(draggingType, originalElementParameters));
            if (element) {
                canvasLayout->addElement(element);
                Selected::getInstance().setSelectedElement(element);
            }
            break;
		}
		case guiElement::TRIANGLE: {
			Triangle* element = dynamic_cast<Triangle*>(factory(draggingType, originalElementParameters));
            if (element) {
                canvasLayout->addElement(element);
                Selected::getInstance().setSelectedElement(element);
            }
            break;
		}
        case guiElement::ELLIPSE: {
            Ellipse* element = dynamic_cast<Ellipse*>(factory(draggingType, originalElementParameters));
            if (element) {
                canvasLayout->addElement(element);
                Selected::getInstance().setSelectedElement(element);
            }
            break;
        }
        case guiElement::ARROW: {
            Arrow* element = dynamic_cast<Arrow*>(factory(draggingType, originalElementParameters));
            if (element) {
                canvasLayout->addElement(element);
                Selected::getInstance().setSelectedElement(element);
            }
            break;
        }
        case guiElement::TEXTBOX: {
            TextBox* element = dynamic_cast<TextBox*>(factory(draggingType, originalElementParameters));
            if (element) {
                canvasLayout->addElement(element);
                Selected::getInstance().setSelectedElement(element);
            }
            break;
        }
        case guiElement::FREEHAND: {
            Freehand* element = dynamic_cast<Freehand*>(factory(draggingType, originalElementParameters));
            if (element) {
                canvasLayout->addElement(element);
                Selected::getInstance().setSelectedElement(element);
            }
            break;
        }
        default: {
            break;
        }
	}
    draggingElement = nullptr;
    draggingType = guiElement::UNKNOWN;
}

void unselect() {
    EventSystem::getInstance().setTargetedElement(nullptr);
    Selected::getInstance().setSelectedElement(nullptr);
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
    playButtonClickSound();
    textbox->appendText(s);
}

bool deleteText() {
    GuiElement* element = Selected::getInstance().getSelectedElement();
    TextBox* textbox = dynamic_cast<TextBox*>(element);
    if (textbox->getText().empty()) {
        deleteShape();
        return false;
    }
    playButtonClickSound();
    textbox->backspace();
    return true;
}

void deleteTempShape() {
    tempLayout->clearElements();
}

void deleteShape() {
    GuiElement* element = Selected::getInstance().getSelectedElement();
    if (element != nullptr) {
        canvasLayout->deleteElement(element->getName());
    }
    tempLayout->clearElements();
}

void updateScreen(DrawingMode mode) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    screen->clear(ivec3(255,255,255));
    EventSystem& eventSystem = EventSystem::getInstance();
    eventSystem.processEvents(rootLayout);
    rootLayout->draw(screen);
    boundingLayout->draw(screen);

    updateActionButtonColors();
    updateToolbarButtonColors(mode);
    
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

void copy() {
    GuiElement* chosen = Selected::getInstance().getSelectedElement();
    if (!chosen) {
        clipboard = ElementParameters();
        clipboardType = guiElement::UNKNOWN;
        return;
    }
    clipboard = chosen->getParameters();
    clipboard.name = "";
    clipboardType = chosen->getType();
}

void paste() {
    if (clipboardType != guiElement::UNKNOWN) {
        ivec2 delta = ivec2(20, 20);
        ElementParameters newObj = clipboard;
        newObj.coords += delta;
        newObj.start += delta;
        newObj.end += delta;
        newObj.min += delta;
        newObj.max += delta;
        newObj.pointA += delta;
        newObj.pointB += delta;
        newObj.pointC += delta;
        newObj.center += delta;
        for (int i = 0; i < newObj.points.size(); ++i) {
            newObj.points[i] += delta;
        }

        switch (clipboardType) {
            case guiElement::POINT: {
                Point* element = dynamic_cast<Point*>(factory(clipboardType, newObj));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::LINE: {
                Line* element = dynamic_cast<Line*>(factory(clipboardType, newObj));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::BOX: {
                Box* element = dynamic_cast<Box*>(factory(clipboardType, newObj));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::TRIANGLE: {
                Triangle* element = dynamic_cast<Triangle*>(factory(clipboardType, newObj));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::ELLIPSE: {
                Ellipse* element = dynamic_cast<Ellipse*>(factory(clipboardType, newObj));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::ARROW: {
                Arrow* element = dynamic_cast<Arrow*>(factory(clipboardType, newObj));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::TEXTBOX: {
                TextBox* element = dynamic_cast<TextBox*>(factory(clipboardType, newObj));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            case guiElement::FREEHAND: {
                Freehand* element = dynamic_cast<Freehand*>(factory(clipboardType, newObj));
                if (element) {
                    canvasLayout->addElement(element);
                    Selected::getInstance().setSelectedElement(element);
                }
                break;
            }
            default: {
                break;
            }
        }
    }
}

bool changeColor(ivec3 colorIncrement) {
    GuiElement* chosen = Selected::getInstance().getSelectedElement();
    if (!chosen) {
        colorIndicator->modifyColor(colorIncrement);
        return false;
    }
    switch(chosen->getType()) {
        case guiElement::POINT: {
            dynamic_cast<Point*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        case guiElement::FREEHAND: {
            dynamic_cast<Freehand*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        case guiElement::LINE: {
            dynamic_cast<Line*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        case guiElement::TEXTBOX: {
            dynamic_cast<TextBox*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        case guiElement::BUTTON: {
            dynamic_cast<Button*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        case guiElement::BOX: {
            dynamic_cast<Box*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        case guiElement::TRIANGLE: {
            dynamic_cast<Triangle*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        case guiElement::ELLIPSE: {
            dynamic_cast<Ellipse*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        case guiElement::ARROW: {
            dynamic_cast<Arrow*>(chosen)->modifyColor(colorIncrement);
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

void updateCursorIcon(const ivec2& point, bool currentlyDragging) {
    GuiElement* hoveredElement = rootLayout->getElementAt(point);

    SDL_Cursor* desiredCursor = (currentlyDragging || hoveredElement) ? handCursor : arrowCursor;
    
    if (currentCursor != desiredCursor) {
        SDL_SetCursor(desiredCursor);
        currentCursor = desiredCursor;
    }
}

bool pressedToolbarButton(const ivec2& point) {
    Button* button = dynamic_cast<Button*>(toolBarLayout->getElementAt(point));
    if (button) {
        pressedButton = button;
        return true;
    }
    return false;
}

bool isInsideSameButton(const ivec2& point) {
    if (pressedButton && pressedButton->isInside(point)) {
        return true;
    }
    return false;
}

void resetPressedButton() {
    pressedButton = nullptr;
}

int requiredPointsForType(guiElement type) {
    switch (type) {
        case guiElement::POINT: {
            return 1; // Point
        }
        case guiElement::LINE:
        case guiElement::BOX:
        case guiElement::TEXTBOX: {
            return 2; // Line, Box, TextBox (all require 2 points to determine shape and orientation)
        }

        case guiElement::TRIANGLE:
        case guiElement::ELLIPSE:
        case guiElement::ARROW: {
            return 3; // Triangle, Ellipse, Arrow (all require 3 points to determine shape and orientation) 
        } 

        default: {
            return 0;
        }
    }
}

guiElement tempElementType(DrawingMode mode) {
    switch (mode) {
        case DrawingMode::POINT: {
            return guiElement::POINT; 
        }

        case DrawingMode::LINE:
        case DrawingMode::TRIANGLE:      // Triangle (draw temp line from point1 to point2, then draw temp triangle when point3 is added)
        case DrawingMode::ELLIPSE: {     // Ellipse (draw temp line from point1 to point2, then draw temp ellipse when point3 is added)
            return guiElement::LINE;
        }

        case DrawingMode::BOX: 
        case DrawingMode::ARROW: // Arrow (draw temp box from point1 to point2, then draw temp arrow when point3 is added)
        case DrawingMode::TEXTBOX: { // TextBox (draw temp box from point1 to point2, then draw temp textbox when point3 is added)
            return guiElement::BOX;
        }
        default: {
            return guiElement::UNKNOWN;
        }
    }
}

guiElement modeToType(DrawingMode mode) {
    switch (mode) {
        case DrawingMode::POINT: {
            return guiElement::POINT;
        }
        case DrawingMode::LINE: {
            return guiElement::LINE;
        }
        case DrawingMode::BOX: {
            return guiElement::BOX;
        }
        case DrawingMode::TRIANGLE: {
            return guiElement::TRIANGLE;
        }
        case DrawingMode::ELLIPSE: {
            return guiElement::ELLIPSE;
        }
        case DrawingMode::ARROW: {
            return guiElement::ARROW;
        }
        case DrawingMode::TEXTBOX: {
            return guiElement::TEXTBOX;
        }
        default: {
            return guiElement::UNKNOWN;
        }
    }
}

void storeCommittedPoint(int points, ivec2 mousePos, ivec2& point1, ivec2& point2, ivec2& point3) {
    if (points == 0) {
        point1 = mousePos;
    }
    else if (points == 1) {
        point2 = mousePos;
    }
    else if (points == 2) { 
        point3 = mousePos;
    }
}

void storeTemporaryPoint(int points, ivec2 mousePos, ivec2& point1, ivec2& point2, ivec2& point3) {
    if (points == 1) {
        point2 = mousePos;
    }
    else if (points == 2) { 
        point3 = mousePos;
    }
}

void resetPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3) {
    point = 0;
    point1.x = std::numeric_limits<int>::lowest();
    point1.y = std::numeric_limits<int>::lowest();
    point2.x = std::numeric_limits<int>::lowest();
    point2.y = std::numeric_limits<int>::lowest();
    point3.x = std::numeric_limits<int>::lowest();
    point3.y = std::numeric_limits<int>::lowest();
}

void playDrawClickSound() {
    EventSystem::getInstance().push(std::make_unique<SoundEvent>("../SFX/draw_click.wav", SoundActionType::PLAY, false));
}

void playButtonClickSound() {
    EventSystem::getInstance().push(std::make_unique<SoundEvent>("../SFX/button_click.wav", SoundActionType::PLAY, false));
}

void playFreehandDrawSound() {
    EventSystem::getInstance().push(std::make_unique<SoundEvent>("../SFX/freehand_draw.wav", SoundActionType::PLAY, false));
}

void playDeleteSound() {
    EventSystem::getInstance().push(std::make_unique<SoundEvent>("../SFX/delete.wav", SoundActionType::PLAY, false));
}