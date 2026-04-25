#include "../API.hpp"
#include "../Global.hpp"
#include <memory>
#include "../Layout.hpp"
#include "../Button.hpp"
#include "../EventSystem.hpp"
#include "../Freehand.hpp"
#include "../MouseDownEvent.hpp"
#include "../MouseMotionEvent.hpp"
#include "../MouseUpEvent.hpp"
#include "../ClickEvent.hpp"

void resetPoints(int& point, ivec2& point1, ivec2& point2, ivec2& point3);

int main() {
    std::cout << "API Demo\n";
    
    DrawingMode mode = DrawingMode::SELECT;
    InteractionState currentInteractionState = InteractionState::IDLE;
    int points = 0;
    ivec2 point1 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point2 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
    ivec2 point3 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());

    Layout* layout = initialize(mode, points, point1, point2, point3);

    loadSound("../SFX/song.wav");
    playSound("../SFX/song.wav", true);
    ivec3 color = ivec3(125, 125, 125);
    std::cout << "Escape to exit drawing mode\nBackspace after selecting an element to delete it\nR/E to increment/decrement red amount\nG/F to increment/decrement green amount\nB/V to increment/decrement blue amount\n";

    ivec2 lastMousePos;
    SDL_Event event;
    EventSystem& eventSystem = EventSystem::getInstance();
    bool end = false;
    while (!end) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    end = true;
                    break;
                }
                case SDL_EVENT_MOUSE_BUTTON_DOWN: {
                    // eventSystem.push(std::make_unique<ClickEvent>(static_cast<int>(event.button.x), static_cast<int>(event.button.y)));
                    // playSound("../SFX/chords.wav", true);
                    int mouseX = static_cast<int>(event.button.x);
                    int mouseY = static_cast<int>(event.button.y);
                    ivec2 mousePos(mouseX, mouseY);

                    Button* button = dynamic_cast<Button*>(layout->getElementAt(mousePos));
                    if (button) {
                        pressedButton = button;
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
                            storePoint(points, mousePos, point1, point2, point3);
                            points++;

                            guiElement type = modeToType(mode);
                            if (points >= requiredPointsForType(type)) {
                                drawElement(type, point1, point2, point3, color);
                                resetPoints(points, point1, point2, point3);
                                mode = DrawingMode::SELECT;
                                currentInteractionState = InteractionState::IDLE;
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

                            GuiElement* hit = canvasLayout->getElementAt(mousePos);
                            if (hit) {
                                lastMousePos = mousePos;
                                Selected::getInstance().setSelectedElement(hit);
                                eventSystem.push(std::make_unique<MouseDownEvent>(lastMousePos));
                                currentInteractionState = InteractionState::DRAGGING;
                                setClickAndDrag(lastMousePos);
                                break;
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
                    switch (currentInteractionState) {
                        case InteractionState::FREEHAND_DRAWING: {
                            if (event.motion.state != 0) {
                                continueFreehandDraw(ivec2(static_cast<int>(event.motion.x), static_cast<int>(event.motion.y)));
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
                        case InteractionState::FREEHAND_DRAWING: {
                            endFreehandDraw(mousePos);
                            currentInteractionState = InteractionState::IDLE;
                            break;
                        }
                        case InteractionState::DRAGGING: {
                            endClickAndDrag();
                            currentInteractionState = InteractionState::IDLE;
                            break;
                        }
                        case InteractionState::TOOLBAR_CLICK: {
                            if (pressedButton && pressedButton->isInside(mousePos)) {
                                unselect();
                                clicked(mousePos);
                            }
                            currentInteractionState = InteractionState::IDLE;
                            break;
                        }
                        case InteractionState::IDLE: {
                            clicked(mousePos);
                            break;
                        }
                        case InteractionState::SHAPE_DRAWING: {
                            break;
                        }
                        default: {
                            break;
                        }
                    }
                    pressedButton = nullptr;
                    
                    break;
                }
                case SDL_EVENT_TEXT_INPUT: {
                    if (isSelectedTextBox()) {
                        appendToTextBox(event.text.text);
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
                                deleteShape();
                                currentInteractionState = InteractionState::IDLE;
                                break;
                            }
                            case SDL_SCANCODE_R: {
                                if (!changeColor(ivec3(1, 0, 0))) {
                                    color.x += 1;
                                    if (color.x > 255) {
                                        color.x = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_G: {
                                if (!changeColor(ivec3(0, 1, 0))) {
                                    color.y += 1;
                                    if (color.y > 255) {
                                        color.y = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_B: {
                                if (!changeColor(ivec3(0, 0, 1))) {
                                    color.z += 1;
                                    if (color.z > 255) {
                                        color.z = 255;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_E: {
                                if (!changeColor(ivec3(-1, 0, 0))) {
                                    color.x -= 1;
                                    if (color.x < 0) {
                                        color.x = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_F: {
                                if (!changeColor(ivec3(0, -1, 0))) {
                                    color.y -= 1;
                                    if (color.y < 0) {
                                        color.y = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_V: {
                                if (!changeColor(ivec3(0, 0, -1))) {
                                    color.z -= 1;
                                    if (color.z < 0) {
                                        color.z = 0;
                                    }
                                }
                                break;
                            }
                            case SDL_SCANCODE_C: {
                                copy();
                                break;
                            }
                            case SDL_SCANCODE_P: {
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
                                deleteText();
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
            updateScreen(mode);
            continue;
        }

        switch (mode) {
            case DrawingMode::LINE:
            case DrawingMode::BOX:
            case DrawingMode::TRIANGLE:
            case DrawingMode::ELLIPSE: 
            case DrawingMode::ARROW:
            case DrawingMode::TEXTBOX: {
                storePoint(points, mousePos, point1, point2, point3);

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

        updateScreen(mode);
    }
    closeAll();
    return 0;
}
