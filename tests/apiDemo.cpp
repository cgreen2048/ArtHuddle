#include "../API.hpp"
#include "../Global.hpp"
#include <memory>
#include "../Layout.hpp"
#include "../EventSystem.hpp"
#include "../MouseDownEvent.hpp"
#include "../MouseMotionEvent.hpp"
#include "../MouseUpEvent.hpp"
#include "../DrawElementMessage.hpp"
#include "../DeleteElementMessage.hpp"
#include "../UpdateElementMessage.hpp"

int main(int argc, char* argv[]) {
    std::cout << "API Demo\n";

    DrawingMode mode = DrawingMode::SELECT;
    InteractionState currentInteractionState = InteractionState::IDLE;
    int points = 0;
    ivec2 point1 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point2 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point3 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec3 color = ivec3(125, 125, 125);

    initialize(mode, points, point1, point2, point3);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    loadSound("../SFX/song2.wav");
    playSound("../SFX/song2.wav", true);
    std::cout << "Escape to exit drawing mode\nBackspace after selecting an element to delete it\nR/E to increment/decrement red amount\nG/F to increment/decrement green amount\nB/V to increment/decrement blue amount\n";

    ivec2 lastMousePos;
    SDL_Event event;
    EventSystem& eventSystem = EventSystem::getInstance();
    Selected& selected = Selected::getInstance();
    bool end = false;
    while (!end) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    end = true;
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    ivec2 mousePos(static_cast<int>(event.button.x), static_cast<int>(event.button.y));

                    if (pressedStartLayoutButton(mousePos) || pressedToolbarButton(mousePos)) {
                        currentInteractionState = InteractionState::TOOLBAR_CLICK;
                        break;
                    }

                    switch (mode) {
                        case DrawingMode::POINT:
                        case DrawingMode::LINE:
                        case DrawingMode::BOX:
                        case DrawingMode::TRIANGLE:
                        case DrawingMode::ELLIPSE:
                        case DrawingMode::ARROW:
                        case DrawingMode::TEXTBOX: {
                            playDrawClickSound();
                            storeCommittedPoint(points, mousePos, point1, point2, point3);
                            points++;

                            guiElement type = modeToType(mode);
                            if (points >= requiredPointsForType(type)) {
                                ElementParameters ep = drawElement(type, point1, point2, point3, color);
                                if (client && client->isConnected()) {
                                    DrawElementMessage message(ep);
                                    client->sendToServer(message.getSerializedMessage());
                                }
                                resetPoints(points, point1, point2, point3);
                                mode = DrawingMode::SELECT;
                                currentInteractionState = InteractionState::SHAPE_COMPLETED;
                                
                            } else {
                                currentInteractionState = InteractionState::SHAPE_DRAWING;
                            }
                            break;
                        }
                        case DrawingMode::FREEHAND_LINE: 
                        case DrawingMode::FREEHAND_SHAPE: {
                            startFreehandDraw(mousePos, color, mode == DrawingMode::FREEHAND_SHAPE);
                            currentInteractionState = InteractionState::FREEHAND_DRAWING;
                            break;
                        }
                        case DrawingMode::SELECT: {
                            // If within another state (dragging, freehand drawing, shape drawing, toolbar click, do not allow select or drag)
                            if (currentInteractionState != InteractionState::IDLE) {
                                break;
                            }

                            // If an element is selected, allow for selecting/dragging that element if mouse within bounding box
                            if (selected.getSelectedElement() != nullptr) {
                                if (selected.isInside(mousePos)) {
                                    if (dynamic_cast<InputTextBox*>(selected.getSelectedElement())) {
                                        clicked(mousePos);
                                        currentInteractionState = InteractionState::IDLE;
                                        break;
                                    }
                                    lastMousePos = mousePos;
                                    eventSystem.push(std::make_unique<MouseDownEvent>(lastMousePos));
                                    currentInteractionState = InteractionState::ELEMENT_PRESSED;
                                    break;
                                }
                            }
                            
                            if (canvasLayout) {
                                GuiElement* hit = canvasLayout->getElementAt(mousePos);
                                if (hit) {
                                    lastMousePos = mousePos;
                                    Selected::getInstance().setSelectedElement(hit);
                                    eventSystem.push(std::make_unique<MouseDownEvent>(lastMousePos));
                                    currentInteractionState = InteractionState::ELEMENT_PRESSED;
                                }
                            }
                            break;
                        }
                        default: {
                            clicked(mousePos);
                            break;
                        }
                    }
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION: {
                    ivec2 mousePos(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y));

                    switch (currentInteractionState) {
                        case InteractionState::FREEHAND_DRAWING: {
                            if (event.motion.state != 0) {
                                playFreehandDrawSound();
                                continueFreehandDraw(ivec2(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y)));
                            }
                            break;
                        }
                        case InteractionState::ELEMENT_PRESSED: {
                            int dx = mousePos.x - lastMousePos.x;
                            int dy = mousePos.y - lastMousePos.y;

                            if (dx * dx + dy * dy > 4) { // small drag threshold
                                currentInteractionState = InteractionState::DRAGGING;
                                setClickAndDrag(lastMousePos);
                                drawClickAndDrag(mousePos);
                            }
                        
                            break;
                        }
                        case InteractionState::DRAGGING: {
                            drawClickAndDrag(ivec2(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y)));
                            break;
                        }
                        default: {
                            break;
                        }
                    }

                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_UP: {
                    ivec2 mousePos(static_cast<int>(event.button.x), static_cast<int>(event.button.y));

                    switch (currentInteractionState) {
                        case InteractionState::IDLE: {
                            clicked(mousePos);
                            break;
                        }
                        case InteractionState::FREEHAND_DRAWING: {
                            ElementParameters ep = endFreehandDraw(mousePos);
                            if (client && client->isConnected()) {
                                DrawElementMessage message(ep);
                                client->sendToServer(message.getSerializedMessage());
                            }
                            currentInteractionState = InteractionState::IDLE;
                            mode = DrawingMode::SELECT;
                            break;
                        }
                        case InteractionState::ELEMENT_PRESSED: {
                            currentInteractionState = InteractionState::IDLE;
                            break;
                        }
                        case InteractionState::DRAGGING: {
                            ElementParameters ep = endClickAndDrag();
                            if (client && client->isConnected()) {
                                UpdateElementMessage message(ep);
                                client->sendToServer(message.getSerializedMessage());
                            }
                            currentInteractionState = InteractionState::IDLE;
                            break;
                        }
                        case InteractionState::TOOLBAR_CLICK: {
                            if (isInsideSameButton(mousePos)) {
                                playButtonClickSound();
                                unselect();
                                clicked(mousePos);
                            }
                            currentInteractionState = InteractionState::IDLE;
                            break;
                        }
                        case InteractionState::SHAPE_COMPLETED: {
                            currentInteractionState = InteractionState::IDLE;
                            break;
                        }
                        case InteractionState::SHAPE_DRAWING: {
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                    resetPressedButton();
                    
                    break;
                }
                case SDL_EVENT_TEXT_INPUT: {
                    if (isSelectedTextBox()) {
                        ElementParameters ep = appendToTextBox(event.text.text);
                        if (client && client->isConnected()) {
                            UpdateElementMessage message(ep);
                            client->sendToServer(message.getSerializedMessage());
                        }
                    }
                    break;
                }
                case SDL_EVENT_KEY_DOWN: {
                    if (!isSelectedTextBox()) {
                        switch (event.key.scancode) {
                            case SDL_SCANCODE_ESCAPE: {
                                mode = DrawingMode::SELECT;
                                resetPoints(points, point1, point2, point3);
                                cancelMove();
                                unselect();
                                currentInteractionState = InteractionState::IDLE;
                                break;
                            }
                            case SDL_SCANCODE_BACKSPACE: {
                                if (currentInteractionState != InteractionState::IDLE || !canvasLayout || selected.getSelectedElement() == nullptr) {
                                    break;
                                }
                                playDeleteSound(); 
                                std::string name = deleteShape();
                                if (client && client->isConnected()) {
                                    DeleteElementMessage message(name);
                                    client->sendToServer(message.getSerializedMessage());
                                }
                                break;
                            }
                            case SDL_SCANCODE_R: {
                                if (!canvasLayout || !colorIndicator) {
                                    break;
                                }

                                if (!changeColor(ivec3(1, 0, 0))) {
                                    color.x += 1;
                                    if (color.x > 255) {
                                        color.x = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_G: {
                                if (!canvasLayout || !colorIndicator) {
                                    break;
                                }

                                if (!changeColor(ivec3(0, 1, 0))) {
                                    color.y += 1;
                                    if (color.y > 255) {
                                        color.y = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_B: {
                                if (!canvasLayout || !colorIndicator) {
                                    break;
                                }

                                if (!changeColor(ivec3(0, 0, 1))) {
                                    color.z += 1;
                                    if (color.z > 255) {
                                        color.z = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_E: {
                                if (!canvasLayout || !colorIndicator) {
                                    break;
                                }

                                if (!changeColor(ivec3(-1, 0, 0))) {
                                    color.x -= 1;
                                    if (color.x < 0) {
                                        color.x = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_F: {
                                if (!canvasLayout || !colorIndicator) {
                                    break;
                                }

                                if (!changeColor(ivec3(0, -1, 0))) {
                                    color.y -= 1;
                                    if (color.y < 0) {
                                        color.y = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_V: {
                                if (!canvasLayout || !colorIndicator) {
                                    break;
                                }

                                if (!changeColor(ivec3(0, 0, -1))) {
                                    color.z -= 1;
                                    if (color.z < 0) {
                                        color.z = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_C: {
                                if (!canvasLayout) {
                                    break;
                                }
                                copy();
                                break;
                            }
                            case SDL_SCANCODE_P: {
                                if (!canvasLayout) {
                                    break;
                                }
                                paste();
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                    else {
                        switch (event.key.scancode) {
                            case SDL_SCANCODE_BACKSPACE: {
                                ElementParameters ep = deleteText();
                                if (ep.toBeDeleted) {
                                    currentInteractionState = InteractionState::IDLE;
                                    if (client && client->isConnected()) {
                                        DeleteElementMessage message(ep.name);
                                        client->sendToServer(message.getSerializedMessage());
                                    }
                                } else {
                                    if (client && client->isConnected()) {
                                        UpdateElementMessage message(ep);
                                        client->sendToServer(message.getSerializedMessage());
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_ESCAPE: {
                                unselect();
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                    break;
                }
            }
        }
        float mouseX = 0;
        float mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        ivec2 mousePos(static_cast<int>(mouseX), static_cast<int>(mouseY));

        if (points == 0) {
            updateScreen(mode, points, point1, point2, point3);
        }
        else {
            switch (mode) {
                case DrawingMode::LINE:
                case DrawingMode::BOX:
                case DrawingMode::TRIANGLE:
                case DrawingMode::ELLIPSE: 
                case DrawingMode::ARROW:
                case DrawingMode::TEXTBOX: {
                    storeTemporaryPoint(points, mousePos, point1, point2, point3);
    
                    guiElement type = modeToType(mode);
                    if (points == requiredPointsForType(type) - 1) {
                        drawTempElement(type, point1, point2, point3, color);
                    }
                    else {
                        drawTempElement(tempElementType(mode), point1, point2, point3, color);
                    }
                    break;
                }
                default: {
                    break;
                }
            }
        }

        updateScreen(mode, points, point1, point2, point3);
        if (server) {
            server->processMessages();
        }
        
        if (client && client->isConnected()) {
            client->processMessages();
        }
    }
    closeAll();
    return 0;
}
