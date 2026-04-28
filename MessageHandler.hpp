#ifndef __MESSAGE_HANDLER_HPP__
#define __MESSAGE_HANDLER_HPP__

#include "JsonDefinition.hpp"
#include "GuiElement.hpp"
#include "Layout.hpp"
#include <string>
#include <queue>
#include <mutex>

class MessageHandler {
    private:
        std::queue<std::string> messageQueue;
        std::mutex queueMutex;
        Layout* canvasLayout;
    public:
        MessageHandler(Layout* layout);
        void push(std::string message);
        bool processMessages();
        bool handleDrawElement(json j);
        bool handleDeleteElement(json j);
        bool handleUpdateElement(json j);
        bool handleInitializeClient(json j);
        Layout* getCanvasLayout();
};


#endif