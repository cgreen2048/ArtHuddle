#include "MessageHandler.hpp"
#include "ElementTypes.hpp"
#include "ElementParameters.hpp"
#include "jsonHelpers.hpp"
#include "Factory.hpp"


MessageHandler::MessageHandler(Layout* layout) : canvasLayout(layout) {}

void MessageHandler::push(std::string message) {
    messageQueue.push(std::move(message));
}

std::optional<std::string> MessageHandler::poll() {
    if (messageQueue.empty()) {
        return std::nullopt;
    }

    std::string message = std::move(messageQueue.front());
    messageQueue.pop();
    return message;
}

bool MessageHandler::processMessage() {
    bool handled = false;
    while (!messageQueue.empty()) {
        auto message = poll();
        
        if (!message) {
            break;
        }

        json j = json::parse(*message);
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
                handled = handleUpdateElement(j);
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
    GuiElement* e = factory(ep.elementType, ep);
    if (e != nullptr) {
        canvasLayout->deleteElement(ep.name);
        canvasLayout->addElement(e);
        return true;
    }
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
