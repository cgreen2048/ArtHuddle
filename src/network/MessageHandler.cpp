#include "ArtHuddle/network/MessageHandler.hpp"
#include "ArtHuddle/core/ElementTypes.hpp"
#include "ArtHuddle/core/MessageTypes.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
#include "ArtHuddle/core/jsonHelpers.hpp"
#include "ArtHuddle/elements/Factory.hpp"
#include "ArtHuddle/utility/Selected.hpp"


MessageHandler::MessageHandler(Layout* layout) : canvasLayout(layout) {}

void MessageHandler::push(std::string message) {
    std::lock_guard<std::mutex> lock(queueMutex);
    messageQueue.push(std::move(message));
}

bool MessageHandler::processMessages() {
    bool handled = false;
    std::queue<std::string> localQueue;

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        std::swap(this->messageQueue, localQueue);
    }

    while (!localQueue.empty()) {
        std::string message = std::move(localQueue.front());
        localQueue.pop();
        
        if (message.empty()) {
            continue;
        }

        json j = json::parse(message);
        MessageType messageType = static_cast<MessageType>(j.at("messageType").get<int>());

        switch (messageType) {
            case MessageType::DRAW_ELEMENT: {
                handled = handleDrawElement(j);
                break;
            }
            case MessageType::DELETE_ELEMENT: {
                handled = handleDeleteElement(j);
                break;
            }
            case MessageType::UPDATE_ELEMENT: {
                handled = handleUpdateElement(j);
                break;
            }
            case MessageType::INITIALIZE_CLIENT: {
                handled = handleInitializeClient(j);
                break;
            }
            default: {
                break;
            }
        }
    }

    return handled;
}

bool MessageHandler::handleDrawElement(json j) {
    ElementParameters ep = jsonToElementParameters(j);
    GuiElement* e = factory(ep.elementType, ep);
    if (e != nullptr) {
        canvasLayout->addElement(e);
        return true;
    }
    return false;
}

bool MessageHandler::handleDeleteElement(json j) {
    std::string elementName = j.at("name").get<std::string>();
    canvasLayout->deleteElement(elementName);
    return true;
}

bool MessageHandler::handleUpdateElement(json j) {
    ElementParameters ep = jsonToElementParameters(j);
    canvasLayout->updateElement(ep);
    return false;
}

bool MessageHandler::handleInitializeClient(json j) {
    canvasLayout->clearElements();
    const auto& elements = j.at("elements");
    for (const auto& el : elements) {
        ElementParameters ep = jsonToElementParameters(el);
        GuiElement* e = factory(ep.elementType, ep);
        if (e != nullptr) {
            canvasLayout->addElement(e);
        }
    }
    return true;
}

Layout* MessageHandler::getCanvasLayout() {
    return this->canvasLayout;
}
