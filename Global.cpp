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
Button* colorIndicator = nullptr;

Uint64 saveFlashUntil = 0;
Uint64 loadFlashUntil = 0;

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

void initButtons(Layout* layout, int& type, int& points, ivec2& point1, ivec2& point2, ivec2& point3) {
    ElementParameters selectButtonParam;
    selectButtonParam.min = ivec2(0, 0);
    selectButtonParam.max = ivec2(bW, bH);
    selectButtonParam.color = ivec3(180, 220, 255);
    selectButtonParam.textColor = ivec3(0, 0, 0);
    selectButtonParam.text = "Select";
    selectButtonParam.name = "selectButton";
    selectButtonParam.callbackName = "setSelectMode";
    selectButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 9;
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
    pointButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 0;
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
    lineButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 1;
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
    boxButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 2;
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
    triangleButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 3;
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
    ellipseButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 4;
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
    arrowButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 5;
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
    textBoxButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 6;
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
    freehandLineButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 7;
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
    freehandShapeButtonParam.callback = [&type, &points, &point1, &point2, &point3]() {
        type = 8;
        resetGlobalPoints(points, point1, point2, point3);
    };
    freehandShapeButton = dynamic_cast<Button *>(factory(guiElement::BUTTON, freehandShapeButtonParam));
    layout->addElement(freehandShapeButton);

    ElementParameters saveButtonParam;
    saveButtonParam.min = ivec2(0, bH + p);
    saveButtonParam.max = ivec2(bigBW, bH + p + bH);
    saveButtonParam.color = ivec3(180, 255, 180);
    saveButtonParam.textColor = ivec3(0, 0, 0);
    saveButtonParam.text = "Save";
    saveButtonParam.name = "saveButton";
    saveButtonParam.callbackName = "saveCanvas";
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
    loadButtonParam.min = ivec2(2 * bigBW + 2 * p, bH + p);
    loadButtonParam.max = ivec2(3 * bigBW + 2 * p, bH + p + bH);
    loadButtonParam.color = ivec3(180, 255, 180);
    loadButtonParam.textColor = ivec3(0, 0, 0);
    loadButtonParam.text = "Load";
    loadButtonParam.name = "loadButton";
    loadButtonParam.callbackName = "loadCanvas";
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
    colorIndicatorParam.min = ivec2(3 * bigBW + 3 * p, bH + p);
    colorIndicatorParam.max = ivec2(4 * bigBW + 3 * p, bH + p + bH);
    colorIndicatorParam.color = ivec3(125, 125, 125);
    colorIndicatorParam.textColor = ivec3(0, 0, 0);
    colorIndicatorParam.text = "Color";
    colorIndicatorParam.name = "colorIndicator";
    colorIndicatorParam.callbackName = "colorIndicator";
    colorIndicatorParam.callback = []() {};
    colorIndicator = dynamic_cast<Button *>(factory(guiElement::BUTTON, colorIndicatorParam));
    layout->addElement(colorIndicator);
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
}

Layout *createRootLayout(int& type, int& points, ivec2& point1, ivec2& point2, ivec2& point3) {
    ElementParameters root;
    root.layoutStart = vec2(0.0, 0.0);
    root.layoutEnd = vec2(1.0, 1.0);
    root.parentStart = ivec2(0, 0);
    root.parentEnd = ivec2(X, Y);
    root.active = true;
    root.name = "rootLayout";
    rootLayout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, root));

    ElementParameters canvas;
    canvas.layoutStart = vec2(0.0, 0.0);
    canvas.layoutEnd = vec2(1.0, 1.0);
    canvas.parentStart = ivec2(0, 0);
    canvas.parentEnd = ivec2(X, Y);
    canvas.active = true;
    canvas.name = "canvasLayout";
    canvasLayout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, canvas));
    rootLayout->addElement(canvasLayout);

    ElementParameters toolBar;
    toolBar.layoutStart = vec2(0.0, 0.0);
    toolBar.layoutEnd = vec2(1.0, 0.2);
    toolBar.parentStart = ivec2(0, 0);
    toolBar.parentEnd = ivec2(X, Y);
    toolBar.active = true;
    toolBar.name = "toolBarLayout";
    toolBarLayout = dynamic_cast<Layout *>(factory(guiElement::LAYOUT, toolBar));
    rootLayout->addElement(toolBarLayout);
    initButtons(toolBarLayout, type, points, point1, point2, point3);

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

    return rootLayout;
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

void updateToolbarButtonColors(int& type) {
    ivec3 normalColor(180, 220, 255);
    ivec3 selectedColor(255, 200, 120);

    if (selectButton) {
        selectButton->setColor(type == 9 ? selectedColor : normalColor, TagType::Vec);
    }
    if (pointButton) {
        pointButton->setColor(type == 0 ? selectedColor : normalColor, TagType::Vec);
    }
    if (lineButton) {
        lineButton->setColor(type == 1 ? selectedColor : normalColor, TagType::Vec);
    }
    if (boxButton) {
        boxButton->setColor(type == 2 ? selectedColor : normalColor, TagType::Vec);
    }
    if (triangleButton) {
        triangleButton->setColor(type == 3 ? selectedColor : normalColor, TagType::Vec);
    }
    if (ellipseButton) {
        ellipseButton->setColor(type == 4 ? selectedColor : normalColor, TagType::Vec);
    }
    if (arrowButton) {
        arrowButton->setColor(type == 5 ? selectedColor : normalColor, TagType::Vec);
    }
    if (textBoxButton) {
        textBoxButton->setColor(type == 6 ? selectedColor : normalColor, TagType::Vec);
    }
    if (freehandLineButton) {
        freehandLineButton->setColor(type == 7 ? selectedColor : normalColor, TagType::Vec);
    }
    if (freehandShapeButton) {
        freehandShapeButton->setColor(type == 8 ? selectedColor : normalColor, TagType::Vec);
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
