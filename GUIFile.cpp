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


void GUIFile::readFile(std::string fileName) {
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
                if(buildingVec2){
                    switch (currentCoord)
                    {
                    case 'x':
                        currentVec2.x = value;
                        break;
                    case 'y':
                        currentVec2.y = value;
                        break;
                    default:
                        std::cerr << "Malformed XML\n";
                        return;
                    }
                }else if(buildingVec3){
                    switch (currentCoord)
                    {
                    case 'x':
                        currentVec3.x = value;
                        break;
                    case 'y':
                        currentVec3.y = value;
                        break;
                    case 'z':
                        currentVec3.z = value;
                        break;
                    default:
                        std::cerr << "Malformed XML\n";
                        return;
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
                    }
                else if (token == BOX_OPEN) {
                    inBox = true;
                    currentBox = Box();
                    boxVec2Index = 0;
                    }
                else if (token == POINT_OPEN) {
                    inPoint = true;
                    currentPoint = Point(); 
                    }
                else if (token == VEC2_OPEN || token == IVEC2_OPEN){
                    buildingVec2 = true;
                    currentVec2 = vec2();
                    }
                else if (token == VEC3_OPEN || token == IVEC3_OPEN){
                    buildingVec3 = true;
                    currentVec3 = vec3();
                    }
                else if (token == X_OPEN){
                   currentCoord = 'x';
                    }
                else if (token == Y_OPEN){
                   currentCoord = 'y';
                    }
                else if (token == Z_OPEN){
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
                    else {
                        if(token == LINE_CLOSE){
                            lines.push_back(currentLine);
                            inLine = false;
                        }
                        else if(token == BOX_CLOSE){
                            boxes.push_back(currentBox);
                            inBox = false;
                        }
                        else if(token == POINT_CLOSE){
                            points.push_back(currentPoint);
                            inPoint = false;
                        }
                        else if (token == VEC2_CLOSE || token == IVEC2_CLOSE){
                            buildingVec2 = false;
                            if(inLine){
                                if (lineVec2Index == 0) currentLine.start = currentVec2;
                                else if(lineVec2Index == 1) currentLine.end = currentVec2;
                                lineVec2Index += 1;
                            }else if(inBox){
                                if (boxVec2Index == 0) currentBox.min = currentVec2;
                                else if(boxVec2Index == 1) currentBox.max = currentVec2;
                                boxVec2Index += 1;
                            }else if(inPoint){
                                currentPoint.position = currentVec2;
                            }
                           
                        }
                        else if (token == VEC3_CLOSE || token == IVEC3_CLOSE){
                            buildingVec3 = false;
                            if(inLine){
                                currentLine.color = currentVec3;
                            }else if(inBox){
                                currentBox.color = currentVec3;
                            }else if(inPoint){
                                currentPoint.color = currentVec3;
                            }
                        }
                        else if (token == X_CLOSE){
                            currentCoord = 0;
                        }
                        else if (token == Y_CLOSE){
                            currentCoord = 0;
                        }
                        else if (token == Z_CLOSE){
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