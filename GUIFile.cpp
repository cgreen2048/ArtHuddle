#include "GUIFile.hpp"



GUIFile::GUIFile() {
    return;
}

GUIFile::~GUIFile() {
    clear();
}

void GUIFile::clear() {
    if (rootLayout != nullptr) {
        delete rootLayout;
        rootLayout = nullptr;
    }
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

static std::string getNextTag(std::ifstream& inFile) {
    char ch;
    std::string tag;

    while (inFile.get(ch)) {
        if (ch == '<') {
            tag += ch;
            break;
        }
    }

    if (tag.empty()) {
        return "";
    }

    while (inFile.get(ch)) {
        tag += ch;
        if (ch == '>') {
            break;
        }
    }

    return tag;
}

static std::string getNextPayload(std::ifstream& inFile) {
    std::string payload;
    char ch;

    while (inFile.get(ch)) {
        if (ch == '<') {
            inFile.unget();  // put back '<'
            break;
        }
        payload += ch;
    }

    return trim(payload);
}

static bool isLayoutOpen(const std::string& tag) {
    return tag.rfind("<layout", 0) == 0 && tag != "</layout>";
}

static bool isLayoutClose(const std::string& tag) {
    return tag == "</layout>";
}

static bool isElementOpen(const std::string& tag) {
    return tag.rfind("<point", 0) == 0 ||
           tag.rfind("<line", 0) == 0 ||
           tag.rfind("<box", 0) == 0 ||
           tag.rfind("<button", 0) == 0 ||
           tag.rfind("<triangle", 0) == 0 ||
           tag.rfind("<ellipse", 0) == 0 ||
           tag.rfind("<arrow", 0) == 0;
}

static guiElement determineGuiElementOpenerType(const std::string& tag) {
    if (tag.rfind("<point", 0) == 0) {
        return guiElement::POINT;
    }
    if (tag.rfind("<line", 0) == 0) {
        return guiElement::LINE;
    }
    if (tag.rfind("<box", 0) == 0) {
        return guiElement::BOX;
    }
    if (tag.rfind("<triangle", 0) == 0) {
        return guiElement::TRIANGLE;
    }
    if (tag.rfind("<button", 0) == 0) {
        return guiElement::BUTTON;
    }
    if (tag.rfind("<ellipse", 0) == 0) {
        return guiElement::ELLIPSE;
    }
    if (tag.rfind("<arrow", 0) == 0) {
        return guiElement::ARROW;
    }

    std::cerr << "Malformed XML\n";
    return guiElement::UNKNOWN;
}

static bool isMatchingElementClose(const std::string& tag, guiElement type) {
    if (type == guiElement::POINT) {
        return tag == POINT_CLOSE;
    }
    if (type == guiElement::LINE) {
        return tag == LINE_CLOSE;
    }
    if (type == guiElement::BOX) {
        return tag == BOX_CLOSE;
    }
    if (type == guiElement::TRIANGLE) {
        return tag == TRIANGLE_CLOSE;
    }
    if (type == guiElement::BUTTON) {
        return tag == BUTTON_CLOSE;
    }
    if (type == guiElement::ELLIPSE) {
        return tag == ELLIPSE_CLOSE;
    }
    if (type == guiElement::ARROW) {
        return tag == ARROW_CLOSE;
    }
    return false;
}

static bool getStringAttribute(const std::string& tag,
                               const std::string& attrName,
                               std::string& value) {
    std::string key = attrName + "=\"";
    size_t start = tag.find(key);

    if (start == std::string::npos) {
        return false;
    }

    start += key.size();
    size_t end = tag.find('"', start);

    if (end == std::string::npos) {
        std::cerr << "Malformed XML\n";
        return false;
    }

    value = tag.substr(start, end - start);
    return true;
}

static bool getFloatAttribute(const std::string& tag,
                                const std::string& attrName,
                                float& value) {
    std::string strValue;
    
    if (!getStringAttribute(tag, attrName, strValue)){
        return false;
    }


    value = std::stof(strValue);
    return true;
}

static bool setNameFromTag(const std::string& tag, ElementParameters* ep) {
    std::string name;

    if (!getStringAttribute(tag, "name", name)) {
        return false;
    }

    ep->name = name;
    return true;
}

static bool setTextFromTag(const std::string& tag, ElementParameters* ep) {
    std::string text;

    if (!getStringAttribute(tag, "text", text)) {
        return false;
    }

    ep->text = text;
    return true;
}

static bool setCallbackNameFromTag(const std::string& tag, ElementParameters* ep) {
    std::string callbackName;

    if (!getStringAttribute(tag, "onClick", callbackName)) {
        return false;
    }

    ep->callbackName = callbackName;
    return true;
}

static bool setRadiusFromTag(const std::string& tag, ElementParameters* ep) {
    float radiusX;
    float radiusY;

    if (!getFloatAttribute(tag, "rx", radiusX)) {
        return false;
    }
    ep->radiusX = static_cast<int>(radiusX);

    if (!getFloatAttribute(tag, "ry", radiusY)) {
        return false;
    }
    ep->radiusY = static_cast<int>(radiusY);

    return true;
}

static bool parseVec2(std::ifstream& inFile, vec2& result) {
    bool hasX = false, hasY = false;

    while (true) {
        std::string tag = getNextTag(inFile);

        if (tag == VEC2_CLOSE) {
            if (!hasX || !hasY) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            return true;
        }

        if (tag == X_OPEN) {
            std::string val = getNextPayload(inFile);
            result.x = std::stof(val);

            if (getNextTag(inFile) != X_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }

            hasX = true;
        }
        else if (tag == Y_OPEN) {
            std::string val = getNextPayload(inFile);
            result.y = std::stof(val);

            if (getNextTag(inFile) != Y_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }

            hasY = true;
        }
        else {
            std::cerr << "Malformed XML\n";
            return false;
        }
    }
}

static bool parseIVec2(std::ifstream& inFile, ivec2& result) {
    bool hasX = false, hasY = false;

    while (true) {
        std::string tag = getNextTag(inFile);

        if (tag == IVEC2_CLOSE) {
            if (!hasX || !hasY) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            return true;
        }

        if (tag == X_OPEN) {
            result.x = std::stoi(getNextPayload(inFile));

            if (getNextTag(inFile) != X_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }

            hasX = true;
        }
        else if (tag == Y_OPEN) {
            result.y = std::stoi(getNextPayload(inFile));

            if (getNextTag(inFile) != Y_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }

            hasY = true;
        }
        else {
            std::cerr << "Malformed XML\n";
            return false;
        }
    }
}

static bool parseVec3(std::ifstream& inFile, vec3& result) {
    bool hasX = false, hasY = false, hasZ = false;

    while (true) {
        std::string tag = getNextTag(inFile);

        if (tag == VEC3_CLOSE) {
            if (!hasX || !hasY || !hasZ) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            return true;
        }

        if (tag == X_OPEN) {
            result.x = std::stof(getNextPayload(inFile));
            if (getNextTag(inFile) != X_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            hasX = true;
        }
        else if (tag == Y_OPEN) {
            result.y = std::stof(getNextPayload(inFile));
            if (getNextTag(inFile) != Y_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            hasY = true;
        }
        else if (tag == Z_OPEN) {
            result.z = std::stof(getNextPayload(inFile));
            if (getNextTag(inFile) != Z_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            hasZ = true;
        }
        else {
            std::cerr << "Malformed XML\n";
            return false;
        }
    }
}

static bool parseIVec3(std::ifstream& inFile, ivec3& result) {
    bool hasX = false, hasY = false, hasZ = false;

    while (true) {
        std::string tag = getNextTag(inFile);

        if (tag == IVEC3_CLOSE) {
            if (!hasX || !hasY || !hasZ) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            return true;
        }

        if (tag == X_OPEN) {
            result.x = std::stoi(getNextPayload(inFile));
            if (getNextTag(inFile) != X_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            hasX = true;
        }
        else if (tag == Y_OPEN) {
            result.y = std::stoi(getNextPayload(inFile));
            if (getNextTag(inFile) != Y_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            hasY = true;
        }
        else if (tag == Z_OPEN) {
            result.z = std::stoi(getNextPayload(inFile));
            if (getNextTag(inFile) != Z_CLOSE) {
                std::cerr << "Malformed XML\n";
                return false;
            }
            hasZ = true;
        }
        else {
            std::cerr << "Malformed XML\n";
            return false;
        }
    }
}

static GuiElement* parseElement(std::ifstream& inFile, const std::string& elementOpenTag) {
    guiElement type = determineGuiElementOpenerType(elementOpenTag);
    ElementParameters ep;

    if (!setNameFromTag(elementOpenTag, &ep)){
        return nullptr;
    }

    if (type == guiElement::BUTTON){
        if(!setCallbackNameFromTag(elementOpenTag, &ep)){
            return nullptr;
        }
        if(!setTextFromTag(elementOpenTag, &ep)){
            return nullptr;
        }
    }

    if (type == guiElement::ELLIPSE) {
        if (!setRadiusFromTag(elementOpenTag, &ep)) {
            return nullptr;
        }
    }


    int lineVec2Index = 0;
    int boxVec2Index = 0;
    int triangleVec2Index = 0;
    bool parsedArrowStem = false;
    bool parsedArrowPoint = false;

    while (true) {
        std::string tag = getNextTag(inFile);

        if (tag.empty()) {
            std::cerr << "Malformed XML\n";
            return nullptr;
        }

        if (isMatchingElementClose(tag, type)) {
            GuiElement* result = factory(type, ep);
            if (!result) {
                std::cerr << "Error creating element\n";
                return nullptr;
            }
            return result;
        }

        if (tag == VEC2_OPEN) {
            vec2 temp;
            if (!parseVec2(inFile, temp)) {
                return nullptr;
            }

            ivec2 v = toIVec2(temp);

            
            if (type == guiElement::LINE) {
                if (lineVec2Index == 0) {
                    ep.start = v;
                    ep.startType = TagType::Vec;
                }
                else {
                    ep.end = v;
                    ep.endType = TagType::Vec;
                }
                lineVec2Index++;
            }
            else if (type == guiElement::BOX || type == guiElement::BUTTON || (type == guiElement::ARROW && parsedArrowStem == false)) {
                if (boxVec2Index == 0) {
                    ep.min = v;
                    ep.minType = TagType::Vec;
                }
                else {
                    ep.max = v;
                    ep.maxType = TagType::Vec;
                    parsedArrowStem = true;
                }
                boxVec2Index++;
            }
            else if (type == guiElement::POINT) {
                ep.coords = v;
                ep.coordsType = TagType::Vec;
            }
            else if (type == guiElement::TRIANGLE || (type == guiElement::ARROW && parsedArrowPoint == false)) {
                if (triangleVec2Index == 0) {
                    ep.pointA = v;
                    ep.pointAType = TagType::Vec;
                }
                else if (triangleVec2Index == 1) {
                    ep.pointB = v;
                    ep.pointBType = TagType::Vec;
                }
                else {
                    ep.pointC = v;
                    ep.pointCType = TagType::Vec;
                    parsedArrowPoint = true;
                }
                triangleVec2Index++;
            }
            else if (type == guiElement::ELLIPSE) {
                ep.center = v;
                ep.centerType = TagType::Vec;
            }
        }
        else if (tag == IVEC2_OPEN) {
            ivec2 v;
            if (!parseIVec2(inFile, v)) {
                return nullptr;
            }

            if (type == guiElement::LINE) {
                if (lineVec2Index == 0) {
                    ep.start = v;
                    ep.startType = TagType::IVec;
                }
                else {
                    ep.end = v;
                    ep.endType = TagType::IVec;
                }
                lineVec2Index++;
            }
            else if (type == guiElement::BOX || type == guiElement::BUTTON || (type == guiElement::ARROW && parsedArrowStem == false)) {
                if (boxVec2Index == 0) {
                    ep.min = v;
                    ep.minType = TagType::IVec;
                }
                else {
                    ep.max = v;
                    ep.maxType = TagType::IVec;
                    parsedArrowStem = true;
                }
                boxVec2Index++;
            }
            else if (type == guiElement::POINT) {
                ep.coords = v;
                ep.coordsType = TagType::IVec;
            }
            else if (type == guiElement::TRIANGLE || (type == guiElement::ARROW && parsedArrowPoint == false)) {
                if (triangleVec2Index == 0) {
                    ep.pointA = v;
                    ep.pointAType = TagType::IVec;
                }
                else if (triangleVec2Index == 1) {
                    ep.pointB = v;
                    ep.pointBType = TagType::IVec;
                }
                else {
                    ep.pointC = v;
                    ep.pointCType = TagType::IVec;
                    parsedArrowPoint = true;
                }
                triangleVec2Index++;
            }
            else if (type == guiElement::ELLIPSE) {
                ep.center = v;
                ep.centerType = TagType::IVec;
            }
        }
        else if (tag == VEC3_OPEN) {
            vec3 temp;
            if (!parseVec3(inFile, temp)) {
                return nullptr;
            }

            ivec3 c = toIVec3(temp);

            ep.color = c;
            ep.colorType = TagType::Vec;
        }
        else if (tag == IVEC3_OPEN) {
            ivec3 c;
            if (!parseIVec3(inFile, c)) {
                return nullptr;
            }
            ep.color = c;
            ep.colorType = TagType::IVec;
        }
        else {
            std::cerr << "Malformed XML\n";
            return nullptr;
        }
    }
}

static Layout* parseLayout(std::ifstream& inFile, const std::string& layoutOpenTag) {
    ElementParameters ep;

    if(!setNameFromTag(layoutOpenTag, &ep)){
        return nullptr;
    }

    float sX, sY, eX, eY;

    if (!getFloatAttribute(layoutOpenTag, "sX", sX) ||
        !getFloatAttribute(layoutOpenTag, "sY", sY) ||
        !getFloatAttribute(layoutOpenTag, "eX", eX) ||
        !getFloatAttribute(layoutOpenTag, "eY", eY)) {
        return nullptr;
    }

    ep.layoutStart = vec2(sX, sY);
    ep.layoutEnd = vec2(eX, eY);

    
    ep.active = true;

    while (true) {
        std::string tag = getNextTag(inFile);

        if (tag.empty()) {
            std::cerr << "Malformed XML\n";
            return nullptr;
        }

        if (isLayoutClose(tag)) {
            GuiElement* result = factory(guiElement::LAYOUT, ep);
            if (!result) {
                std::cerr << "Error creating layout\n";
            }
            return static_cast<Layout*>(result);
        }

        if (isLayoutOpen(tag)) {
            Layout* childLayout = parseLayout(inFile, tag);
            if (!childLayout) {
                return nullptr;
            }
            ep.elements.push_back(childLayout);
        }
        else if (isElementOpen(tag)) {
            GuiElement* child = parseElement(inFile, tag);
            if (!child) {
                return nullptr;
            }
            ep.elements.push_back(child);
        }
        else {
            std::cerr << "Malformed XML\n";
            return nullptr;
        }
    }
}

Layout* GUIFile::getRootLayout() const {
    return rootLayout;
}

void GUIFile::setRootLayout(Layout* root) {
    if (rootLayout != nullptr) {
        delete rootLayout;
    }
    rootLayout = root;
}

void GUIFile::readFile(const std::string& fileName) {
    clear();

    std::ifstream inFile(fileName);
    if (!inFile.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::string firstTag = getNextTag(inFile);

    if (!isLayoutOpen(firstTag)) {
        std::cerr << "Malformed XML\n";
        return;
    }

    rootLayout = parseLayout(inFile, firstTag);
}

void GUIFile::writeFile(const std::string& fileName) const {
    std::ofstream out(fileName);
    if (!out.is_open()) {
        return;
    }
    
    if (!rootLayout) {
        std::cerr << "No layout to write\n";
        return;
    }
    rootLayout->writeXml(out);
}