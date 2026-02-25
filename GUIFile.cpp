#include "GUIFile.hpp"


GUIFile::GUIFile() {
    return;
}

std::string trim(const std::string& s) {
    size_t first = s.find_first_not_of(" \t\n\r");
    if (first == std::string::npos)
        return "";

    size_t last = s.find_last_not_of(" \t\n\r");
    return s.substr(first, last - first + 1);
}

const std::vector<GUIFile::Line>& GUIFile::getLines() const {
    return lines;
}
const std::vector<GUIFile::Box>& GUIFile::getBoxes() const { 
    return boxes; 
}
const std::vector<GUIFile::Point>& GUIFile::getPoints() const { 
    return points; 
}

void GUIFile::addLine(const Line& l) { 
    lines.push_back(l); 
}
void GUIFile::addBox(const Box& b) { 
    boxes.push_back(b); 
}
void GUIFile::addPoint(const Point& p) { 
    points.push_back(p); 
}

void GUIFile::clear() {
    lines.clear();
    boxes.clear();
    points.clear();
}


void GUIFile::readFile(std::string fileName) {
    clear();
    
    std::ifstream inFile{fileName};
    if (!inFile.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    Line  currentLine;
    Box   currentBox;
    Point currentPoint;
    bool inLine  = false;
    bool inBox   = false;
    bool inPoint = false;

    vec2 currentVec2;
    vec3 currentVec3;
    bool buildingVec2 = false;
    bool buildingVec3 = false;
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
            if (start == std::string::npos) break;
            std::string payload = line.substr(0, start);
            payload = trim(payload);

            if (!payload.empty() && currentCoord != 0 && (buildingVec2 || buildingVec3) ) {
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
            }
            

            line.erase(0, start);

            end = line.find('>');
            if (end == std::string::npos) break;
            

            std::string token = line.substr(0, end + 1);
            line.erase(0, end + 1);

            auto locator = std::find(OPENERS.begin(), OPENERS.end(), token);
            if (locator != OPENERS.end()) { 
                matcher.push(token);
                if (token == LINE_OPEN) {
                    inLine = true;
                    currentLine = Line();      // reset it
                    lineVec2Index = 0;         // first vec2 will be start
                    buildingVec2 = false;
                    buildingVec3 = false;
                }
                else if (token == BOX_OPEN) {
                    inBox = true;
                    currentBox = Box();
                    boxVec2Index = 0;
                    buildingVec2 = false;
                    buildingVec3 = false;
                }
                else if (token == POINT_OPEN) {
                    inPoint = true;
                    currentPoint = Point();
                    buildingVec2 = false;
                    buildingVec3 = false;
                }
                else if (token == VEC2_OPEN || token == IVEC2_OPEN) {
                    buildingVec2 = true;
                    capturedX = false;
                    capturedY = false;
                    currentVec2 = vec2();
                    buildingVec3 = false;
                }
                else if (token == VEC3_OPEN || token == IVEC3_OPEN) {
                    buildingVec3 = true;
                    capturedX = false;
                    capturedY = false;
                    capturedZ = false;
                    currentVec3 = vec3();
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
                    if (matcher.empty()) { std::cerr << "Malformed XML\n"; return; } // In case XML starts with a closer
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
                    // else if ((buildingVec2 && (!capturedX || !capturedY)) || 
                    //     (buildingVec3 && (!capturedX || !capturedY || !capturedZ))) {
                    //         std::cerr << "Malformed XML\n";
                    //         return;
                    // }
                    else {
                        if (token == LINE_CLOSE){
                            lines.push_back(currentLine);
                            inLine = false;
                        }
                        else if (token == BOX_CLOSE){
                            boxes.push_back(currentBox);
                            inBox = false;
                        }
                        else if (token == POINT_CLOSE){
                            points.push_back(currentPoint);
                            inPoint = false;
                        }
                        else if (token == VEC2_CLOSE || token == IVEC2_CLOSE){
                            if (!capturedX || !capturedY) {
                                std::cerr << "Malformed XML\n";
                                return;
                            }
                            buildingVec2 = false;
                            if (inLine) {
                                if (lineVec2Index == 0) currentLine.start = currentVec2;
                                else if(lineVec2Index == 1) currentLine.end = currentVec2;
                                lineVec2Index += 1;
                            }
                            else if (inBox) {
                                if (boxVec2Index == 0) {
                                    currentBox.min = currentVec2;
                                }
                                else if (boxVec2Index == 1) {
                                    currentBox.max = currentVec2;
                                }
                                boxVec2Index += 1;
                            }
                            else if (inPoint) {
                                currentPoint.position = currentVec2;
                            }
                           
                        }
                        else if (token == VEC3_CLOSE || token == IVEC3_CLOSE) {
                            if (!capturedX || !capturedY || !capturedZ) {
                                std::cerr << "Malformed XML\n";
                                return;
                            }
                            buildingVec3 = false;
                            if (inLine) {
                                currentLine.color = currentVec3;
                            }
                            else if (inBox) {
                                currentBox.color = currentVec3;
                            }
                            else if(inPoint) {
                                currentPoint.color = currentVec3;
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


void GUIFile::writeFile(const std::string& fileName) const {
    std::ofstream out(fileName);
    if (!out.is_open()) {
        return;
    }

    out << "<layout>\n";

    // Write lines
    for (const auto& l : lines) {
        out << "  <line>\n";

        // write start vec2
        out << "    <vec2>\n";
        out << "        <x>" << l.start.x  << "</x>\n";
        out << "        <y>" << l.start.y  << "</y>\n";
        out << "    </vec2>\n";
        
        // write end vec2
        out << "    <vec2>\n";
        out << "        <x>" << l.end.x  << "</x>\n";
        out << "        <y>" << l.end.y  << "</y>\n";
        out << "    </vec2>\n";

        // write color vec3
        out << "    <vec3>\n";
        out << "        <x>" << l.color.x  << "</x>\n";
        out << "        <y>" << l.color.y  << "</y>\n";
        out << "        <z>" << l.color.z  << "</z>\n";
        out << "    </vec3>\n";

        out << "  </line>\n";
    }

    // Write boxes
    for (const auto& b : boxes) {
        out << "  <box>\n";

        // write min vec2
        out << "    <vec2>\n";
        out << "        <x>" << b.min.x  << "</x>\n";
        out << "        <y>" << b.min.y  << "</y>\n";
        out << "    </vec2>\n";
        
        // write max vec2
        out << "    <vec2>\n";
        out << "        <x>" << b.max.x  << "</x>\n";
        out << "        <y>" << b.max.y  << "</y>\n";
        out << "    </vec2>\n";

        // write color vec3
        out << "    <vec3>\n";
        out << "        <x>" << b.color.x  << "</x>\n";
        out << "        <y>" << b.color.y  << "</y>\n";
        out << "        <z>" << b.color.z  << "</z>\n";
        out << "    </vec3>\n";

        out << "  </box>\n";
    }

    // // Write points
    for (const auto& p : points) {
        out << "  <point>\n";

        // write position vec2
        out << "    <vec2>\n";
        out << "        <x>" << p.position.x  << "</x>\n";
        out << "        <y>" << p.position.y  << "</y>\n";
        out << "    </vec2>\n";
        

        // write color vec3
        out << "    <vec3>\n";
        out << "        <x>" << p.color.x  << "</x>\n";
        out << "        <y>" << p.color.y  << "</y>\n";
        out << "        <z>" << p.color.z  << "</z>\n";
        out << "    </vec3>\n";

        out << "  </point>\n";
    }

    out << "</layout>\n";
}