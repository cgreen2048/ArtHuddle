#include "Global.hpp"

SDL_Window *window = nullptr;
Screen *screen = nullptr;
SoundPlayer *soundPlayer = nullptr;
Layout *rootLayout = nullptr;
Layout *toolBarLayout = nullptr;
Layout *canvasLayout = nullptr;
Layout *tempLayout = nullptr;
Layout* boundingLayout = nullptr;
SDL_Renderer *renderer = nullptr;
GuiElement* draggingElement = nullptr;
guiElement draggingType = guiElement::UNKNOWN;
ElementParameters originalElementParameters;
ElementParameters draggingElementParameters;
ivec2 lastMousePos;
ElementParameters clipboard;
guiElement clipboardType = guiElement::UNKNOWN;
std::filesystem::path currentFileLoadPath = "";
std::filesystem::path currentFileSavePath = "";
SDL_Cursor* arrowCursor = nullptr;
SDL_Cursor* handCursor  = nullptr;
SDL_Cursor* currentCursor = nullptr;
Button* pressedButton = nullptr;

// int type = 9;
// int points = 0;
// ivec2 point1 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
// ivec2 point2 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());
// ivec2 point3 = ivec2(std::numeric_limits<int>::lowest(), std::numeric_limits<int>::lowest());

Button *selectButton = nullptr;
Button *pointButton = nullptr;
Button *lineButton = nullptr;
Button *boxButton = nullptr;
Button *triangleButton = nullptr;
Button *ellipseButton = nullptr;
Button *arrowButton = nullptr;
Button *textBoxButton = nullptr;
Button *freehandLineButton = nullptr;
Button *freehandShapeButton = nullptr;
Button *saveButton = nullptr;
Button *loadButton = nullptr;
Button *muteButton = nullptr;
Button* colorIndicator = nullptr;
Button* startDrawingButton = nullptr;
Button* connectToHostButton = nullptr;

Uint64 saveFlashUntil = 0;
Uint64 loadFlashUntil = 0;

std::unique_ptr<RelayServer> server = nullptr;
std::unique_ptr<ClientNetwork> client = nullptr;
std::string connectedHost = "";
bool isHost = false;
std::thread serverThread;

InputTextBox* hostIpTextBox = nullptr;
Button* submitHostIpButton = nullptr;

bool pendingStartHost = false;
bool pendingJoinHost = false;
bool pendingDisconnect = false;
std::string pendingHostIp = "";
Button* disconnectButton = nullptr;
Button* welcomeMessage = nullptr;


struct FileDialogData {
    int*points;
    ivec2* point1;
    ivec2* point2;
    ivec2* point3;
};

static void SDLCALL loadFileCallback(void* userdata, const char* const* filelist, int filter) {
    if (!filelist || !*filelist) return;

    FileDialogData* dialogData = static_cast<FileDialogData*>(userdata);

    std::filesystem::path absolutePath = filelist[0];
    std::filesystem::path relativePath = std::filesystem::relative(absolutePath, std::filesystem::current_path());
    currentFileLoadPath = relativePath;

    loadCanvas(currentFileLoadPath.string(), *dialogData->points, *dialogData->point1, *dialogData->point2, *dialogData->point3);

    delete dialogData;
}

static void SDLCALL saveFileCallback(void* userdata, const char* const* filelist, int filter) {
    if (!filelist || !*filelist) return;

    std::filesystem::path absolutePath = filelist[0];
    std::filesystem::path relativePath = std::filesystem::relative(absolutePath, std::filesystem::current_path());
    currentFileSavePath = relativePath;

    saveCanvas(currentFileSavePath.string());
}

void initButtons(Layout* layout, DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3) {

    int row2Y1 = bH + p;
    int row2Y2 = 2 * bH + p;

    int row3Y1 = 2 * bH + 2 * p;
    int row3Y2 = 3 * bH + 2 * p;

    int x = 0;

    ElementParameters selectButtonParam;
    selectButtonParam.min = ivec2(0, 0);
    selectButtonParam.max = ivec2(bW, bH);
    selectButtonParam.color = ivec3(180, 220, 255);
    selectButtonParam.textColor = ivec3(0, 0, 0);
    selectButtonParam.text = "Select";
    selectButtonParam.name = "selectButton";
    selectButtonParam.callbackName = "setSelectMode";
    selectButtonParam.active = true;
    selectButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::SELECT;
        resetGlobalPoints(points, point1, point2, point3);
    };
    selectButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, selectButtonParam));
    layout->addElement(selectButton);

    ElementParameters pointButtonParam;
    pointButtonParam.min = ivec2(bW + p, 0);
    pointButtonParam.max = ivec2(2 * bW + p, bH);
    pointButtonParam.color = ivec3(180, 220, 255);
    pointButtonParam.textColor = ivec3(0, 0, 0);
    pointButtonParam.text = "Point";
    pointButtonParam.name = "pointButton";
    pointButtonParam.callbackName = "setPointMode";
    pointButtonParam.active = true;
    pointButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::POINT;
        resetGlobalPoints(points, point1, point2, point3);
    };
    pointButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, pointButtonParam));
    layout->addElement(pointButton);

    ElementParameters lineButtonParam;
    lineButtonParam.min = ivec2(2 * bW + 2 * p, 0);
    lineButtonParam.max = ivec2(3 * bW + 2 * p, bH);
    lineButtonParam.color = ivec3(180, 220, 255);
    lineButtonParam.textColor = ivec3(0, 0, 0);
    lineButtonParam.text = "Line";
    lineButtonParam.name = "lineButton";
    lineButtonParam.callbackName = "setLineMode";
    lineButtonParam.active = true;
    lineButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::LINE;
        resetGlobalPoints(points, point1, point2, point3);
    };
    lineButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, lineButtonParam));
    layout->addElement(lineButton);

    ElementParameters boxButtonParam;
    boxButtonParam.min = ivec2(3 * bW + 3 * p, 0);
    boxButtonParam.max = ivec2(4 * bW + 3 * p, bH);
    boxButtonParam.color = ivec3(180, 220, 255);
    boxButtonParam.textColor = ivec3(0, 0, 0);
    boxButtonParam.text = "Box";
    boxButtonParam.name = "boxButton";
    boxButtonParam.callbackName = "setBoxMode";
    boxButtonParam.active = true;
    boxButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::BOX;
        resetGlobalPoints(points, point1, point2, point3);
    };
    boxButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, boxButtonParam));
    layout->addElement(boxButton);

    ElementParameters triangleButtonParam;
    triangleButtonParam.min = ivec2(4 * bW + 4 * p, 0);
    triangleButtonParam.max = ivec2(5 * bW + 4 * p, bH);
    triangleButtonParam.color = ivec3(180, 220, 255);
    triangleButtonParam.textColor = ivec3(0, 0, 0);
    triangleButtonParam.text = "Triangle";
    triangleButtonParam.name = "triangleButton";
    triangleButtonParam.callbackName = "setTriangleMode";
    triangleButtonParam.active = true;
    triangleButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::TRIANGLE;
        resetGlobalPoints(points, point1, point2, point3);
    };
    triangleButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, triangleButtonParam));
    layout->addElement(triangleButton);

    ElementParameters ellipseButtonParam;
    ellipseButtonParam.min = ivec2(5 * bW + 5 * p, 0);
    ellipseButtonParam.max = ivec2(6 * bW + 5 * p, bH);
    ellipseButtonParam.color = ivec3(180, 220, 255);
    ellipseButtonParam.textColor = ivec3(0, 0, 0);
    ellipseButtonParam.text = "Ellipse";
    ellipseButtonParam.name = "ellipseButton";
    ellipseButtonParam.callbackName = "setEllipseMode";
    ellipseButtonParam.active = true;
    ellipseButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::ELLIPSE;
        resetGlobalPoints(points, point1, point2, point3);
    };
    ellipseButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, ellipseButtonParam));
    layout->addElement(ellipseButton);

    ElementParameters arrowButtonParam;
    arrowButtonParam.min = ivec2(6 * bW + 6 * p, 0);
    arrowButtonParam.max = ivec2(7 * bW + 6 * p, bH);
    arrowButtonParam.color = ivec3(180, 220, 255);
    arrowButtonParam.textColor = ivec3(0, 0, 0);
    arrowButtonParam.text = "Arrow";
    arrowButtonParam.name = "arrowButton";
    arrowButtonParam.callbackName = "setArrowMode";
    arrowButtonParam.active = true;
    arrowButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::ARROW;
        resetGlobalPoints(points, point1, point2, point3);
    };
    arrowButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, arrowButtonParam));
    layout->addElement(arrowButton);

    ElementParameters textBoxButtonParam;
    textBoxButtonParam.min = ivec2(7 * bW + 7 * p, 0);
    textBoxButtonParam.max = ivec2(8 * bW + 7 * p, bH);
    textBoxButtonParam.color = ivec3(180, 220, 255);
    textBoxButtonParam.textColor = ivec3(0, 0, 0);
    textBoxButtonParam.text = "Text Box";
    textBoxButtonParam.name = "textBoxButton";
    textBoxButtonParam.callbackName = "setTextBoxMode";
    textBoxButtonParam.active = true;
    textBoxButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::TEXTBOX;
        resetGlobalPoints(points, point1, point2, point3);
    };
    textBoxButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, textBoxButtonParam));
    layout->addElement(textBoxButton);

    ElementParameters freehandLineButtonParam;
    freehandLineButtonParam.min = ivec2(8 * bW + 8 * p, 0);
    freehandLineButtonParam.max = ivec2(8 * bW + 8 * p + bigBW, bH);
    freehandLineButtonParam.color = ivec3(180, 220, 255);
    freehandLineButtonParam.textColor = ivec3(0, 0, 0);
    freehandLineButtonParam.text = "Freehand Line";
    freehandLineButtonParam.name = "freehandLineButton";
    freehandLineButtonParam.callbackName = "setFreehandLineMode";
    freehandLineButtonParam.active = true;
    freehandLineButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::FREEHAND_LINE;
        resetGlobalPoints(points, point1, point2, point3);
    };
    freehandLineButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, freehandLineButtonParam));
    layout->addElement(freehandLineButton);

    ElementParameters freehandShapeButtonParam;
    freehandShapeButtonParam.min = ivec2(8 * bW + 8 * p + bigBW + p, 0);
    freehandShapeButtonParam.max = ivec2(8 * bW + 8 * p + 2 * bigBW + p, bH);
    freehandShapeButtonParam.color = ivec3(180, 220, 255);
    freehandShapeButtonParam.textColor = ivec3(0, 0, 0);
    freehandShapeButtonParam.text = "Freehand Shape";
    freehandShapeButtonParam.name = "freehandShapeButton";
    freehandShapeButtonParam.callbackName = "setFreehandShapeMode";
    freehandShapeButtonParam.active = true;
    freehandShapeButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        mode = DrawingMode::FREEHAND_SHAPE;
        resetGlobalPoints(points, point1, point2, point3);
    };
    freehandShapeButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, freehandShapeButtonParam));
    layout->addElement(freehandShapeButton);

    

    ElementParameters saveButtonParam;
    saveButtonParam.min = ivec2(x, row2Y1);
    saveButtonParam.max = ivec2(x + bigBW, row2Y2);
    x += bigBW + p;
    saveButtonParam.color = ivec3(180, 255, 180);
    saveButtonParam.textColor = ivec3(0, 0, 0);
    saveButtonParam.text = "Save";
    saveButtonParam.name = "saveButton";
    saveButtonParam.callbackName = "saveCanvas";
    saveButtonParam.active = true;
    saveButtonParam.callback = []() {
        if (currentFileSavePath.empty()) {
            SDL_ShowSaveFileDialog(
                saveFileCallback,
                nullptr,
                window,
                nullptr,  // filters (optional)
                0,
                nullptr  // default location
            );
        } else {
            saveCanvas(currentFileSavePath.string());
        }
        
        saveFlashUntil = SDL_GetTicks() + 700; // flash for 300 ms
    };
    saveButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, saveButtonParam));
    layout->addElement(saveButton);

    ElementParameters loadButtonParam;
    loadButtonParam.min = ivec2(x, row2Y1);
    loadButtonParam.max = ivec2(x + bigBW, row2Y2);
    x += bigBW + p;
    loadButtonParam.textColor = ivec3(0, 0, 0);
    loadButtonParam.text = "Load";
    loadButtonParam.name = "loadButton";
    loadButtonParam.callbackName = "loadCanvas";
    loadButtonParam.active = true;
    loadButtonParam.callback = [&points, &point1, &point2, &point3]() {
        FileDialogData* dialogData = new FileDialogData{&points, &point1, &point2, &point3};
        SDL_ShowOpenFileDialog(
            loadFileCallback,
            dialogData, // userdata
            window,
            nullptr,   // filters
            0,         // number of filters
            nullptr,   // default location
            false      // allow multiple files
        );

        loadFlashUntil = SDL_GetTicks() + 700; // flash for 300 ms
    };
    loadButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, loadButtonParam));
    layout->addElement(loadButton);

    ElementParameters colorIndicatorParam;
    colorIndicatorParam.min = ivec2(x, row2Y1);
    colorIndicatorParam.max = ivec2(x + bigBW, row2Y2);
    x += bigBW + p;
    colorIndicatorParam.color = ivec3(125, 125, 125);
    colorIndicatorParam.textColor = ivec3(0, 0, 0);
    colorIndicatorParam.text = "Color";
    colorIndicatorParam.name = "colorIndicator";
    colorIndicatorParam.callbackName = "colorIndicator";
    colorIndicatorParam.active = true;
    colorIndicatorParam.callback = []() {};
    colorIndicator = dynamic_cast<Button *>(factory(guiElement::BUTTON, colorIndicatorParam));
    layout->addElement(colorIndicator);

    ElementParameters muteButtonParam;
    muteButtonParam.min = ivec2(x, row2Y1);
    muteButtonParam.max = ivec2(x + bigBW, row2Y2);
    x += bigBW + p;
    muteButtonParam.color = ivec3(180, 255, 180);
    muteButtonParam.textColor = ivec3(0, 0, 0);
    muteButtonParam.text = "Mute";
    muteButtonParam.name = "muteButton";
    muteButtonParam.callbackName = "toggleMute";
    muteButtonParam.active = true;
    muteButtonParam.callback = []() {
        soundPlayer->toggleMute();
        muteButton->setText(soundPlayer->isMuted() ? "Unmute" : "Mute");
    };
    muteButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, muteButtonParam));
    layout->addElement(muteButton);

    ElementParameters  disconnectButtonParam;
    disconnectButtonParam.min = ivec2(x, row2Y1);
    disconnectButtonParam.max = ivec2(x + bigBW, row2Y2);
    x += bigBW + p;
    disconnectButtonParam.color = ivec3(180, 255, 180);
    disconnectButtonParam.textColor = ivec3(0, 0, 0);
    disconnectButtonParam.text = "Disconnect";
    disconnectButtonParam.name = "disconnectButton";
    disconnectButtonParam.callbackName = "disconnectClient";
    disconnectButtonParam.active = true;
    disconnectButtonParam.callback = []() {
    pendingDisconnect = true;
    };
    disconnectButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, disconnectButtonParam));
    layout->addElement(disconnectButton);
}

void createWindow() {
    window = SDL_CreateWindow("ArtHuddle", X, Y, 0);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << '\n';
        SDL_Quit();
    }
}

void createScreen() {
    renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << '\n';
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    screen = new Screen(X, Y, renderer);

    arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
    handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
    currentCursor = arrowCursor;
    SDL_SetCursor(currentCursor);
}

Layout *createStartMenuLayout(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3) {
    ElementParameters root;
    root.layoutStart = vec2(0.0, 0.0);
    root.layoutEnd = vec2(1.0, 1.0);
    root.parentStart = ivec2(0, 0);
    root.parentEnd = ivec2(X, Y);
    root.active = true;
    root.name = "startMenuRoot";

    rootLayout = dynamic_cast<Layout*>(
        factory(guiElement::LAYOUT, root)
    );

    int row1Y1 = 0;
    int row1Y2 = bH;

    int row2Y1 = bH + p;
    int row2Y2 = 2 * bH + p;

    int x = 0;

    ElementParameters startDrawingButtonParam;
    startDrawingButtonParam.min = ivec2(x, row1Y1);
    startDrawingButtonParam.max = ivec2(x + 2 * bigBW, row1Y2);
    x += 2 * bigBW + p;
    startDrawingButtonParam.color = ivec3(180, 255, 180);
    startDrawingButtonParam.textColor = ivec3(0, 0, 0);
    startDrawingButtonParam.text = "Start Drawing as Host";
    startDrawingButtonParam.name = "startDrawingButton";
    startDrawingButtonParam.callbackName = "startDrawing";
    startDrawingButtonParam.active = true;
    startDrawingButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        pendingStartHost = true;
        // client->startReceiveThread();
    };
    startDrawingButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, startDrawingButtonParam));
    rootLayout->addElement(startDrawingButton);

    ElementParameters connectToHostButtonParam;
    connectToHostButtonParam.min = ivec2(x, row1Y1);
    connectToHostButtonParam.max = ivec2(x + bigBW, row1Y2);
    x += bigBW + p;
    connectToHostButtonParam.color = ivec3(180, 255, 180);
    connectToHostButtonParam.textColor = ivec3(0, 0, 0);
    connectToHostButtonParam.text = "Connect";
    connectToHostButtonParam.name = "connectToHost";
    connectToHostButtonParam.callbackName = "connect";
    connectToHostButtonParam.active = true;
    connectToHostButtonParam.callback = []() {
        // Show textbox
       if (hostIpTextBox) {
        hostIpTextBox->setActive(true); // focus for typing
        hostIpTextBox->setVisible(true);
    }

        if (submitHostIpButton) {
            submitHostIpButton->setActive(true);
        }

        SDL_StartTextInput(window);

    };
    connectToHostButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, connectToHostButtonParam));
    rootLayout->addElement(connectToHostButton);


    ElementParameters welcomeParam;
    welcomeParam.min = ivec2(centerX - 3*bigBW / 2, centerY - bH /2);
    welcomeParam.max = ivec2(centerX + 3*bigBW / 2, centerY + bH /2);
    welcomeParam.color = ivec3(180, 255, 180);
    welcomeParam.textColor = ivec3(0, 0, 0);
    welcomeParam.text = "Welcome to ArtHuddle!";
    welcomeParam.name = "welcomeMessage";
    welcomeParam.callbackName = "none";
    welcomeParam.active = true;
    welcomeParam.callback = []() {}; // Do nothing.
    welcomeMessage = dynamic_cast<Button *>(factory(guiElement::BUTTON, welcomeParam));
    rootLayout->addElement(welcomeMessage);

    x = 0;

    ElementParameters hostIpTextBoxParam;
    hostIpTextBoxParam.min = ivec2(x, row2Y1);
    hostIpTextBoxParam.max = ivec2(x + bigBW, row2Y2);
    x += 4* bigBW + p;
    hostIpTextBoxParam.color = ivec3(255, 0, 0);
    hostIpTextBoxParam.textColor = ivec3(0, 0, 0);
    hostIpTextBoxParam.name = "hostIpTextBox";
    hostIpTextBoxParam.active = false;
    hostIpTextBox =  dynamic_cast<InputTextBox*>(factory(guiElement::INPUTTEXTBOX, hostIpTextBoxParam));
    rootLayout->addElement(hostIpTextBox);

    ElementParameters submitHostIpButtonParam;
    submitHostIpButtonParam.min = ivec2(x, row2Y1);
    submitHostIpButtonParam.max = ivec2(x + bigBW, row2Y2);
    x += bigBW + p;
    submitHostIpButtonParam.color = ivec3(180, 255, 180);
    submitHostIpButtonParam.textColor = ivec3(0, 0, 0);
    submitHostIpButtonParam.text = "Join";
    submitHostIpButtonParam.name = "submitHostIpButton";
    submitHostIpButtonParam.callbackName = "submitHostIp";
    submitHostIpButtonParam.active = false;
    submitHostIpButtonParam.callback = [&mode, &points, &point1, &point2, &point3]() {
        if (!hostIpTextBox) {
            std::cout << "Host IP textbox missing\n";
            return;
        }

        std::string ip = hostIpTextBox->getText();

        if (ip.empty()) {
            std::cout << "No IP entered\n";
            return;
        }

        pendingHostIp = ip;
        pendingJoinHost = true;
    };
    submitHostIpButton = dynamic_cast<Button*>(
        factory(guiElement::BUTTON, submitHostIpButtonParam)
    );
    rootLayout->addElement(submitHostIpButton);

    return rootLayout;
}

void switchToDrawingLayout(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3) {
    delete rootLayout;

    rootLayout = nullptr;
    toolBarLayout = nullptr;
    canvasLayout = nullptr;
    tempLayout = nullptr;
    boundingLayout = nullptr;

    saveButton = nullptr;
    loadButton = nullptr;
    colorIndicator = nullptr;

    hostIpTextBox = nullptr;
    submitHostIpButton = nullptr;

    Selected::getInstance().setSelectedElement(nullptr);
    EventSystem::getInstance().setTargetedElement(nullptr);

    createDrawingLayout(mode, points, point1, point2, point3);

    mode = DrawingMode::SELECT;
    resetGlobalPoints(points, point1, point2, point3);
    updateToolbarButtonColors(mode);

}

void createDrawingLayout(DrawingMode& mode, int& points, ivec2& point1, ivec2& point2, ivec2& point3) {
    ElementParameters root;
    root.layoutStart = vec2(0.0, 0.0);
    root.layoutEnd = vec2(1.0, 1.0);
    root.parentStart = ivec2(0, 0);
    root.parentEnd = ivec2(X, Y);
    root.active = true;
    root.name = "rootLayout";
    rootLayout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, root));

    ElementParameters toolBar;
    toolBar.layoutStart = vec2(0.0, 0.0);
    toolBar.layoutEnd = vec2(1.0, 0.35);
    toolBar.parentStart = ivec2(0, 0);
    toolBar.parentEnd = ivec2(X, Y);
    toolBar.active = true;
    toolBar.name = "toolBarLayout";
    toolBarLayout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, toolBar));
    rootLayout->addElement(toolBarLayout);
    initButtons(toolBarLayout, mode, points, point1, point2, point3);

    ElementParameters canvas;
    canvas.layoutStart = vec2(0.0, 0.0);
    canvas.layoutEnd = vec2(1.0, 1.0);
    canvas.parentStart = ivec2(0, 0);
    canvas.parentEnd = ivec2(X, Y);
    canvas.active = true;
    canvas.name = "canvasLayout";
    canvasLayout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, canvas));
    server = std::make_unique<RelayServer>(canvasLayout);
    client = std::make_unique<ClientNetwork>(canvasLayout);
    rootLayout->addElement(canvasLayout);

    ElementParameters temp;
    temp.layoutStart = vec2(0.0, 0.0);
    temp.layoutEnd = vec2(1.0, 1.0);
    temp.parentStart = ivec2(0, 0);
    temp.parentEnd = ivec2(X, Y);
    temp.active = true;
    temp.name = "tempLayout";
    tempLayout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, temp));
    rootLayout->addElement(tempLayout);

   
    Selected &selectedSingleton = Selected::getInstance();
    ElementParameters boundingLayoutParam;
    boundingLayoutParam.layoutStart = vec2(0.0, 0.0);
    boundingLayoutParam.layoutEnd = vec2(1.0, 1.0);
    boundingLayoutParam.parentStart = ivec2(0, 0);
    boundingLayoutParam.parentEnd = ivec2(X, Y);
    boundingLayoutParam.active = true;
    boundingLayoutParam.name = "boundingLayout";
    boundingLayout = dynamic_cast<Layout*>(factory(guiElement::LAYOUT, boundingLayoutParam));
    selectedSingleton.setSelectedLayout(boundingLayout);
    // rootLayout->addElement(boundingLayout);

    
}

void setEventSystem() {
    EventSystem &eventSystem = EventSystem::getInstance();
    soundPlayer = new SoundPlayer();
    eventSystem.setSoundPlayer(soundPlayer);
}

void resetGlobalPoints(int &points, ivec2 &point1, ivec2 &point2, ivec2 &point3) {
    points = 0;
    point1.x = std::numeric_limits<int>::lowest();
    point1.y = std::numeric_limits<int>::lowest();
    point2.x = std::numeric_limits<int>::lowest();
    point2.y = std::numeric_limits<int>::lowest();
    point3.x = std::numeric_limits<int>::lowest();
    point3.y = std::numeric_limits<int>::lowest();
}

void saveCanvas(const std::string &filePath) {
    std::ofstream out(filePath);
    if (!out){
        std::cerr << "Failed to open file for saving: " << filePath << '\n';
        return;
    }

    if (!canvasLayout) {
        std::cerr << "canvasLayout is null\n";
        return;
    }

    canvasLayout->writeXml(out);
}


void loadCanvas(const std::string& filePath, int& points, ivec2& point1, ivec2& point2, ivec2& point3) {
    GUIFile guiFile;
    guiFile.readFile(filePath);

    Layout* loadedLayout = guiFile.getRootLayout();
    if (!loadedLayout) {
        std::cerr << "Failed to load file: " << filePath << '\n';
        return;
    }

    canvasLayout->clearElements();

    for (GuiElement* el : loadedLayout->getElements()) {
        if (el) {
            canvasLayout->addElement(el->clone());
        }
    }

    tempLayout->clearElements();
    Selected::getInstance().setSelectedElement(nullptr);
    resetGlobalPoints(points, point1, point2, point3);
}

void updateToolbarButtonColors(DrawingMode mode) {
    ivec3 normalColor(180, 220, 255);
    ivec3 selectedColor(255, 200, 120);

    if (selectButton) {
        selectButton->setColor(mode == DrawingMode::SELECT ? selectedColor : normalColor, TagType::Vec);
    }
    if (pointButton) {
        pointButton->setColor(mode == DrawingMode::POINT ? selectedColor : normalColor, TagType::Vec);
    }
    if (lineButton) {
        lineButton->setColor(mode == DrawingMode::LINE ? selectedColor : normalColor, TagType::Vec);
    }
    if (boxButton) {
        boxButton->setColor(mode == DrawingMode::BOX ? selectedColor : normalColor, TagType::Vec);
    }
    if (triangleButton) {
        triangleButton->setColor(mode == DrawingMode::TRIANGLE ? selectedColor : normalColor, TagType::Vec);
    }
    if (ellipseButton) {
        ellipseButton->setColor(mode == DrawingMode::ELLIPSE ? selectedColor : normalColor, TagType::Vec);
    }
    if (arrowButton) {
        arrowButton->setColor(mode == DrawingMode::ARROW ? selectedColor : normalColor, TagType::Vec);
    }
    if (textBoxButton) {
        textBoxButton->setColor(mode == DrawingMode::TEXTBOX ? selectedColor : normalColor, TagType::Vec);
    }
    if (freehandLineButton) {
        freehandLineButton->setColor(mode == DrawingMode::FREEHAND_LINE ? selectedColor : normalColor, TagType::Vec);
    }
    if (freehandShapeButton) {
        freehandShapeButton->setColor(mode == DrawingMode::FREEHAND_SHAPE ? selectedColor : normalColor, TagType::Vec);
    }
}

void updateActionButtonColors() {
    ivec3 normalColor(180, 220, 255);
    ivec3 flashColor(180, 255, 180);

    Uint64 now = SDL_GetTicks();

    if (saveButton) {
        if (now < saveFlashUntil) {
            saveButton->setColor(flashColor, TagType::Vec);
        } else {
            saveButton->setColor(normalColor, TagType::Vec);
        }
    }

    if (loadButton) {
        if (now < loadFlashUntil) {
            loadButton->setColor(flashColor, TagType::Vec);
        } else {
            loadButton->setColor(normalColor, TagType::Vec);
        }
    }
}

void updateLoadSavePermissions() {
    if (!isHost && !connectedHost.empty()) {
        loadButton->setActive(false);
    } else {
        loadButton->setActive(true);
    }

    saveButton->setActive(true);
}

void resetGlobalState() {
    rootLayout = nullptr;
    toolBarLayout = nullptr;
    canvasLayout = nullptr;
    tempLayout = nullptr;
    boundingLayout = nullptr;

    selectButton = nullptr;
    pointButton = nullptr;
    lineButton = nullptr;
    boxButton = nullptr;
    triangleButton = nullptr;
    ellipseButton = nullptr;
    arrowButton = nullptr;
    textBoxButton = nullptr;
    freehandLineButton = nullptr;
    freehandShapeButton = nullptr;

    saveButton = nullptr;
    loadButton = nullptr;
    muteButton = nullptr;
    colorIndicator = nullptr;

    startDrawingButton = nullptr;
    connectToHostButton = nullptr;

    hostIpTextBox = nullptr;
    submitHostIpButton = nullptr;

    pressedButton = nullptr;

    draggingElement = nullptr;
    draggingType = guiElement::UNKNOWN;

    connectedHost = "";
    isHost = false;

    Selected::getInstance().setSelectedElement(nullptr);
    EventSystem::getInstance().setTargetedElement(nullptr);
}



