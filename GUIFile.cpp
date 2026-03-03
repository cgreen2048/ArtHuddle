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
    guiElement currentType;
    bool inLine  = false;
    bool inBox   = false;
    bool inPoint = false;

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
                                    return;
                                }
                                break;
                            }
                            default: {
                                std::cerr << "Malformed XML\n";
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
                                    return; 
                                }
                                break;

                            case 'y':
                                if (!capturedY) { 
                                    currentIVec2.y = value; capturedY = true; 
                                }
                                else {
                                    std::cerr << "Malformed XML\n";
                                    return;
                                }
                                break;

                            default: {
                                std::cerr << "Malformed XML\n";
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
                                    return;
                                }
                                break;
                            }
                            default: {
                                std::cerr << "Malformed XML\n";
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
                                    return;
                                }
                                break;
                            }
                            default: {
                                std::cerr << "Malformed XML\n";
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
                    inLine = true;
                    current = factory(guiElement::LINE) // reset it
                    lineVec2Index = 0;         // first vec2 will be start
                    buildingVec2 = false;
                    buildingIVec2 = false;
                    buildingVec3 = false;
                    buildingIVec3 = false;
                }
                else if (token == BOX_OPEN) {
                    inBox = true;
                    currentBox = Box();
                    boxVec2Index = 0;
                    buildingVec2 = false;
                    buildingIVec2 = false;
                    buildingVec3 = false;
                    buildingIVec3 = false;
                }
                else if (token == POINT_OPEN) {
                    inPoint = true;
                    currentPoint = Point();
                    buildingVec2 = false;
                    buildingIVec2 = false;
                    buildingVec3 = false;
                    buildingIVec3 = false;
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
                            return;
                        }
                    else {
                        if (token == LINE_CLOSE) {
                            lines.push_back(current);
                            inLine = false;
                        }
                        else if (token == BOX_CLOSE) {
                            boxes.push_back(current);
                            inBox = false;
                        }
                        else if (token == POINT_CLOSE) {
                            points.push_back(current);
                            inPoint = false;
                        }
                        else if (token == VEC2_CLOSE) {
                            if (!capturedX || !capturedY) {
                                std::cerr << "Malformed XML\n";
                                return;
                            }
                            buildingVec2 = false;
                            if (inLine) {
                                if (lineVec2Index == 0) {
                                    currentLine.start = currentVec2;
                                    currentLine.startType = TagType::Vec;
                                }
                                else if(lineVec2Index == 1) {
                                    currentLine.end = currentVec2;
                                    currentLine.endType = TagType::Vec;
                                }
                                lineVec2Index += 1;
                            }
                            else if (inBox) {
                                if (boxVec2Index == 0) {
                                    currentBox.min = currentVec2;
                                    currentBox.minType = TagType::Vec;
                                }
                                else if (boxVec2Index == 1) {
                                    currentBox.max = currentVec2;
                                    currentBox.maxType = TagType::Vec;
                                }
                                boxVec2Index += 1;
                            }
                            else if (inPoint) {
                                currentPoint.position = currentVec2;
                                currentPoint.posType = TagType::Vec;
                            } 
                        }
                        else if (token == IVEC2_CLOSE) {
                            if (!capturedX || !capturedY) {
                                std::cerr << "Malformed XML\n";
                                return;
                            }
                            buildingIVec2 = false;
                            vec2 converted(static_cast<float>(currentIVec2.x), static_cast<float>(currentIVec2.y));
                            if (inLine) {
                                if (lineVec2Index == 0) {
                                    currentLine.start = converted;
                                    currentLine.startType = TagType::IVec;
                                }
                                else if(lineVec2Index == 1) {
                                    currentLine.end = converted;
                                    currentLine.endType = TagType::IVec;
                                }
                                lineVec2Index += 1;
                            }
                            else if (inBox) {
                                if (boxVec2Index == 0) {
                                    currentBox.min = converted;
                                    currentBox.minType = TagType::IVec;
                                }
                                else if (boxVec2Index == 1) {
                                    currentBox.max = converted;
                                    currentBox.maxType = TagType::IVec;
                                }
                                boxVec2Index += 1;
                            }
                            else if (inPoint) {
                                currentPoint.position = converted;
                                currentPoint.posType = TagType::IVec;
                            }
                        }
                        else if (token == VEC3_CLOSE) {
                            if (!capturedX || !capturedY || !capturedZ) {
                                std::cerr << "Malformed XML\n";
                                return;
                            }
                            buildingVec3 = false;
                            if (inLine) {
                                currentLine.color = currentVec3;
                                currentLine.colorType = TagType::Vec;
                            }
                            else if (inBox) {
                                currentBox.color = currentVec3;
                                currentBox.colorType = TagType::Vec;
                            }
                            else if(inPoint) {
                                currentPoint.color = currentVec3;
                                currentPoint.colorType = TagType::Vec;
                            }
                        }
                        else if (token == IVEC3_CLOSE) {
                            if (!capturedX || !capturedY || !capturedZ) {
                                std::cerr << "Malformed XML\n";
                                return;
                            }
                            buildingIVec3 = false;
                            vec3 converted(static_cast<float>(currentIVec3.x), static_cast<float>(currentIVec3.y),
                            static_cast<float>(currentIVec3.z));
                            if (inLine) {
                                currentLine.color = converted;
                                currentLine.colorType = TagType::IVec;
                            }
                            else if (inBox) {
                                currentBox.color = converted;
                                currentBox.colorType = TagType::IVec;
                            }
                            else if(inPoint) {
                                currentPoint.color = converted;
                                currentPoint.colorType = TagType::IVec;
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
    }
    return;
}

static int toInt(float x) {
    return static_cast<int>(std::lround(x));
}

static void writeVec2(std::ofstream& out, const vec2& v) {
    out << "    <vec2>\n";
    out << "        <x>" << v.x  << "</x>\n";
    out << "        <y>" << v.y  << "</y>\n";
    out << "    </vec2>\n";
}

static void writeIVec2(std::ofstream& out, const vec2& v) {
    out << "    <ivec2>\n";
    out << "        <x>" << toInt(v.x)  << "</x>\n";
    out << "        <y>" << toInt(v.y)  << "</y>\n";
    out << "    </ivec2>\n";
}

static void writeVec3(std::ofstream& out, const vec3& v) {
    out << "    <vec3>\n";
    out << "        <x>" << v.x  << "</x>\n";
    out << "        <y>" << v.y  << "</y>\n";
    out << "        <z>" << v.z  << "</z>\n";
    out << "    </vec3>\n";
}

static void writeIVec3(std::ofstream& out, const vec3& v) {
    out << "    <ivec3>\n";
    out << "        <x>" << toInt(v.x)  << "</x>\n";
    out << "        <y>" << toInt(v.y)  << "</y>\n";
    out << "        <z>" << toInt(v.z)  << "</z>\n";
    out << "    </ivec3>\n";
}


void GUIFile::writeFile(const std::string& fileName) const {
    std::ofstream out(fileName);
    if (!out.is_open()) {
        return;
    }

    out << "<layout>\n";

    for (const auto& l : lines) {
        out << "  <line>\n";

        if (l.startType == TagType::IVec){ 
            writeIVec2(out, l.start);
        }
        else {
            writeVec2(out, l.start);
        }

        if (l.endType == TagType::IVec) {
            writeIVec2(out, l.end);
        }
        else { 
            writeVec2(out, l.end);
        }

        if (l.colorType == TagType::IVec) { 
            writeIVec3(out, l.color);
        }
        else { 
            writeVec3(out, l.color);
        }

        out << "  </line>\n";
    }

    for (const auto& b : boxes) {
        out << "  <box>\n";

        if (b.minType == TagType::IVec) {
            writeIVec2(out, b.min);
        }
        else {
            writeVec2(out, b.min);
        }

        if (b.maxType == TagType::IVec) {
            writeIVec2(out, b.max);
        }
        else {
            writeVec2(out, b.max);
        }

        if (b.colorType == TagType::IVec) { 
            writeIVec3(out, b.color);
        }
        else {
            writeVec3(out, b.color);
        }

        out << "  </box>\n";
    }

    for (const auto& p : points) {
        out << "  <point>\n";

        if (p.posType == TagType::IVec) {
            writeIVec2(out, p.position);
        }
        else {
            writeVec2(out, p.position);
        }

        if (p.colorType == TagType::IVec) {
            writeIVec3(out, p.color);
        }
        else {
            writeVec3(out, p.color);
        }

        out << "  </point>\n";
    }

    out << "</layout>\n";
}