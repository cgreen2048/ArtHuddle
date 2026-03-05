#include "GUIFile.hpp"



GUIFile::GUIFile() {
    return;
}

GUIFile::~GUIFile() {
    clear();
}

void GUIFile::clear() {
    for (GuiElement* e : elements) {
        delete e;
    }
    elements.clear();
}

const std::vector<GuiElement*>& GUIFile::getElements() const {
    return elements;
}

void GUIFile::addLine(Line* l) {
    elements.push_back(l); // implicit upcast Line* -> GuiElement*
}

void GUIFile::addBox(Box* b) {
    elements.push_back(b);
}

void GUIFile::addPoint(Point* p) {
    elements.push_back(p);
}

static int toInt(float x) {
    return static_cast<int>(std::lround(x));
}

static ivec2 toIVec2(const vec2& v) {
    return ivec2(toInt(v.x), toInt(v.y));
}

static ivec3 toIVec3(const vec3& v) {
    return ivec3(toInt(v.x), toInt(v.y), toInt(v.z));
}

static vec2 toVec2(const ivec2& v) {
    return vec2(static_cast<float>(v.x), static_cast<float>(v.y));
}

static vec3 toVec3(const ivec3& v) {
    return vec3(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z));
}

static std::string trim(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) {
        return "";
    }

    size_t last = s.find_last_not_of(" \t\n\r");
    return s.substr(first, last - first + 1);
}

void GUIFile::readFile(std::string fileName) {
    clear();
    
    std::ifstream inFile{fileName};
    if (!inFile.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    GuiElement* current = nullptr;
    guiElement currentType = guiElement::POINT; // any default
    // bool inElement = false;


    vec2 currentVec2;
    ivec2 currentIVec2;
    vec3 currentVec3;
    ivec3 currentIVec3;

    bool buildingVec2 = false;
    bool buildingIVec2 = false;
    bool buildingVec3 = false;
    bool buildingIVec3 = false;

    bool capturedX = false;
    bool capturedY = false;
    bool capturedZ = false;

    char currentCoord = 0;   // 0 means “not capturing”

    int lineVec2Index = 0;
    int boxVec2Index = 0;

    std::stack<std::string> matcher;
    std::string line;
    size_t start = 0;
    size_t end = 0;
    while(std::getline(inFile, line)) {
        while (1) {
            start = line.find('<');
            if (start == std::string::npos) {
                break;
            }
            std::string payload = line.substr(0, start);
            payload = trim(payload);

            if (!payload.empty() && currentCoord != 0 && (buildingVec2 || buildingIVec2 
                || buildingVec3 || buildingIVec3)) {
                    float value = std::stof(payload);
                    if (buildingVec2) {
                        switch (currentCoord) {
                            case 'x': {
                                if (!capturedX) {
                                    currentVec2.x = value;
                                    capturedX = true;
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;
                            }
                            case 'y': {
                                if (!capturedY) {
                                    currentVec2.y = value;
                                    capturedY = true;
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;
                            }
                            default: {
                                std::cerr << "Malformed XML\n";
                                if (current) { 
                                    delete current; 
                                    current = nullptr; 
                                }
                                return;
                            }
                        }
                    }
                    else if (buildingIVec2) {
                        int value = std::stoi(payload);
                        switch (currentCoord) {
                            case 'x':
                                if (!capturedX) { 
                                    currentIVec2.x = value; capturedX = true; 
                                }
                                else { 
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return; 
                                }
                                break;

                            case 'y':
                                if (!capturedY) { 
                                    currentIVec2.y = value; capturedY = true; 
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;

                            default: {
                                std::cerr << "Malformed XML\n";
                                if (current) { 
                                    delete current; 
                                    current = nullptr; 
                                }
                                return;
                            }
                        }
                    }
                    else if (buildingVec3) {
                        switch (currentCoord) {
                            case 'x': {
                                if (!capturedX) {
                                    currentVec3.x = value;
                                    capturedX = true;
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;
                            }
                            case 'y': {
                                if (!capturedY) {
                                    currentVec3.y = value;
                                    capturedY = true;
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;
                            }
                            case 'z': {
                                if (!capturedZ) {
                                    currentVec3.z = value;
                                    capturedZ = true;
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;
                            }
                            default: {
                                std::cerr << "Malformed XML\n";
                                if (current) { 
                                    delete current; 
                                    current = nullptr; 
                                }
                                return;
                            }
                        }
                    }
                    else if (buildingIVec3) {
                        int value = std::stoi(payload);
                        switch (currentCoord) {
                            case 'x': {
                                if (!capturedX) {
                                    currentIVec3.x = value;
                                    capturedX = true;
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;
                            }
                            case 'y': {
                                if (!capturedY) {
                                    currentIVec3.y = value;
                                    capturedY = true;
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;
                            }
                            case 'z': {
                                if (!capturedZ) {
                                    currentIVec3.z = value;
                                    capturedZ = true;
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    if (current) { 
                                        delete current; 
                                        current = nullptr; 
                                    }
                                    return;
                                }
                                break;
                            }
                            default: {
                                std::cerr << "Malformed XML\n";
                                if (current) { 
                                    delete current; 
                                    current = nullptr; 
                                }
                                return;
                            }
                        }
                    }
                }
            
            line.erase(0, start);

            end = line.find('>');
            if (end == std::string::npos) {
                break;
            }
            

            std::string token = line.substr(0, end + 1);
            line.erase(0, end + 1);

            auto locator = std::find(OPENERS.begin(), OPENERS.end(), token);
            if (locator != OPENERS.end()) { 
                matcher.push(token);
                if (token == LINE_OPEN) {
                    currentType = guiElement::LINE;
                    current = factory(currentType);        // returns new Line
                    lineVec2Index = 0;
                }
                else if (token == BOX_OPEN) {
                    currentType = guiElement::BOX;
                    current = factory(currentType);        // returns new Box
                    boxVec2Index = 0;
                }
                else if (token == POINT_OPEN) {
                    currentType = guiElement::POINT;
                    current = factory(currentType);        // returns new Point
                }
                else if (token == VEC2_OPEN) {
                    buildingVec2 = true;
                    buildingIVec2 = false;
                    capturedX = false;
                    capturedY = false;
                    currentVec2 = vec2();
                    buildingVec3 = false;
                    buildingIVec3 = false;
                }
                 else if (token == IVEC2_OPEN) {
                    buildingIVec2 = true;
                    buildingVec2 = false;
                    capturedX = false;
                    capturedY = false;
                    currentIVec2 = ivec2();
                    buildingIVec3 = false;
                    buildingVec3 = false;
                }
                else if (token == VEC3_OPEN) {
                    buildingVec3 = true;
                    buildingIVec3 = false;
                    capturedX = false;
                    capturedY = false;
                    capturedZ = false;
                    currentVec3 = vec3();
                    buildingVec2 = false;
                    buildingIVec2 = false;
                }
                else if (token == IVEC3_OPEN) {
                    buildingIVec3 = true;
                    buildingVec3 = false;
                    capturedX = false;
                    capturedY = false;
                    capturedZ = false;
                    currentIVec3 = ivec3();
                    buildingIVec2 = false;
                    buildingVec2 = false;
                }
                else if (token == X_OPEN) {
                   currentCoord = 'x';
                }
                else if (token == Y_OPEN) {
                   currentCoord = 'y';
                }
                else if (token == Z_OPEN) {
                   currentCoord = 'z';
                }
            }     
            else {
                locator = std::find(CLOSERS.begin(), CLOSERS.end(), token);
                if (locator != CLOSERS.end()) {
                    if (matcher.empty()) {  // In case XML starts with a closer
                        std::cerr << "Malformed XML\n";
                        if (current) { 
                            delete current; 
                            current = nullptr; 
                        } 
                        return;
                    }
                    std::string top = matcher.top();
                    if ((token == LAYOUT_CLOSE && top != LAYOUT_OPEN) ||
                        (token == LINE_CLOSE && top != LINE_OPEN) ||
                        (token == BOX_CLOSE && top != BOX_OPEN) ||
                        (token == POINT_CLOSE && top != POINT_OPEN) ||
                        (token == VEC2_CLOSE && top != VEC2_OPEN) ||
                        (token == VEC3_CLOSE && top != VEC3_OPEN) ||
                        (token == IVEC2_CLOSE && top != IVEC2_OPEN) ||
                        (token == IVEC3_CLOSE && top != IVEC3_OPEN) ||
                        (token == X_CLOSE && top != X_OPEN) ||
                        (token == Y_CLOSE && top != Y_OPEN) ||
                        (token == Z_CLOSE && top != Z_OPEN)) {
                            // bad scenario, malformed
                            std::cerr << "Malformed XML\n";
                            if (current) { 
                                delete current; 
                                current = nullptr; 
                            }
                            return;
                        }
                        else if (token == LINE_CLOSE || token == BOX_CLOSE || token == POINT_CLOSE) {
                            if (!current) { 
                                std::cerr << "Malformed XML\n"; 
                                return; 
                            }
                            elements.push_back(current);
                            current = nullptr;
                        }
                        else if (token == VEC2_CLOSE) {
                            if (!capturedX || !capturedY) { 
                                std::cerr << "Malformed XML\n"; 
                                if (current) { 
                                    delete current; 
                                    current = nullptr; 
                                }
                                return; 
                            }
                            buildingVec2 = false;

                            ivec2 v = toIVec2(currentVec2);

                            if (currentType == guiElement::LINE) {
                                auto* l = static_cast<Line*>(current);
                                if (lineVec2Index == 0) {
                                    l->setStart(v, Line::TagType::Vec);
                                }
                                else {
                                    l->setEnd(v, Line::TagType::Vec);
                                }
                                lineVec2Index++;
                            }
                            else if (currentType == guiElement::BOX) {
                                auto* b = static_cast<Box*>(current);
                                if (boxVec2Index == 0) {
                                    b->setMin(v, Box::TagType::Vec);
                                }
                                else {
                                    b->setMax(v, Box::TagType::Vec);
                                }
                                boxVec2Index++;
                            }
                            else if (currentType == guiElement::POINT) {
                                auto* p = static_cast<Point*>(current);
                                p->setCoords(v, Point::TagType::Vec);
                            }
                        }
                        else if (token == IVEC2_CLOSE) {
                            if (!capturedX || !capturedY) { 
                                std::cerr << "Malformed XML\n"; 
                                if (current) { 
                                    delete current; 
                                    current = nullptr; 
                                }
                                return; 
                            }
                            buildingIVec2 = false;

                            ivec2 v = currentIVec2;

                            if (currentType == guiElement::LINE) {
                                auto* l = static_cast<Line*>(current);
                                if (lineVec2Index == 0) {
                                    l->setStart(v, Line::TagType::IVec);
                                }
                                else {
                                    l->setEnd(v,   Line::TagType::IVec);
                                }
                                lineVec2Index++;
                            }
                            else if (currentType == guiElement::BOX) {
                                auto* b = static_cast<Box*>(current);
                                if (boxVec2Index == 0) {
                                    b->setMin(v, Box::TagType::IVec);
                                }
                                else {
                                    b->setMax(v, Box::TagType::IVec);
                                }
                                boxVec2Index++;
                            }
                            else if (currentType == guiElement::POINT) {
                                auto* p = static_cast<Point*>(current);
                                p->setCoords(v, Point::TagType::IVec);
                            }
                        }
                        else if (token == VEC3_CLOSE) {
                            if (!capturedX || !capturedY || !capturedZ) { 
                                std::cerr << "Malformed XML\n"; 
                                if (current) { 
                                    delete current; 
                                    current = nullptr; 
                                }
                                return; 
                            }
                            buildingVec3 = false;

                            ivec3 c = toIVec3(currentVec3);

                            if (currentType == guiElement::LINE) {
                                static_cast<Line*>(current)->setColor(c, Line::TagType::Vec);
                            } else if (currentType == guiElement::BOX) {
                                static_cast<Box*>(current)->setColor(c, Box::TagType::Vec);
                            } else if (currentType == guiElement::POINT) {
                                static_cast<Point*>(current)->setColor(c, Point::TagType::Vec);
                            }
                        }
                        else if (token == IVEC3_CLOSE) {
                            if (!capturedX || !capturedY || !capturedZ) { 
                                std::cerr << "Malformed XML\n"; 
                                if (current) { 
                                    delete current; 
                                    current = nullptr; 
                                }
                                return; 
                            }
                            buildingIVec3 = false;

                            ivec3 c = currentIVec3;

                            if (currentType == guiElement::LINE) {
                                static_cast<Line*>(current)->setColor(c, Line::TagType::IVec);
                            } else if (currentType == guiElement::BOX) {
                                static_cast<Box*>(current)->setColor(c, Box::TagType::IVec);
                            } else if (currentType == guiElement::POINT) {
                                static_cast<Point*>(current)->setColor(c, Point::TagType::IVec);
                            }
                        }
                        else if (token == X_CLOSE) {
                            currentCoord = 0;
                        }
                        else if (token == Y_CLOSE) {
                            currentCoord = 0;
                        }
                        else if (token == Z_CLOSE) {
                            currentCoord = 0;
                        }
                        matcher.pop();
                }
            }
        }
    }
    return;
}



void GUIFile::writeFile(const std::string& fileName) const {
    std::ofstream out(fileName);
    if (!out.is_open()) {
        return;
    }
    
    out << "<layout>\n";
    for (auto* e : elements) {
        e->writeXml(out);
    }
    out << "</layout>\n";
}