#ifndef __MESSAGE_HANDLER_HPP__
#define __MESSAGE_HANDLER_HPP__

#include "JsonDefinition.hpp"
#include "GuiElement.hpp"
#include "Layout.hpp"
#include <string>
#include <queue>
#include <optional>

class MessageHandler {
    private:
        std::queue<std::string> messageQueue;
        Layout* canvasLayout;
    public:
        MessageHandler(Layout* layout);
        void push(std::string message);
        std::optional<std::string> poll();
        bool processMessages();
        bool handleDrawElement(json j);
        bool handleDeleteElement(json j);
        bool handleUpdateElement(json j);
        bool handleInitializeClient(json j);
};


#endif