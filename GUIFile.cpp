#include "GUIFile.hpp"


GUIFile::GUIFile() {
    return;
}



void GUIFile::readFile(std::string fileName) {
    std::ifstream inFile{fileName};
    if (!inFile.is_open()) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::stack<std::string> matcher;
    std::string line;
    int start = 0;
    int end = 0;
    while(std::getline(inFile, line)) {
        if (inFile.eof()) break;
        while (1) {
            start = line.find('<');
            if (start == 1) break;
            end = line.find('>');
            if (end == -1) break;
            std::string token = line.substr(start, end-start+1);
            auto locator = std::find(OPENERS.begin(), OPENERS.end(), token);
            if (locator != OPENERS.end()) {
                matcher.push(token);
            }
            else {
                locator = std::find(CLOSERS.begin(), CLOSERS.end(), token);
                if (locator != CLOSERS.end()) {
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
                        matcher.pop();
                    }
                }
            }
            line.erase(start, end-start+1);
        }
    }


    for (int i = 0; i < matcher.size(); ++i) {
        std::cout << matcher.top() << '\n';
        matcher.pop();
    }


    // std::stack<std::string> holder;
    // std::string line;
    // std::stringstream ss;

    // std::getline(inFile, line);
    // ss << line;

    // std::string token;
    // while (ss >> token) {
    //     std::cout << token << std::endl;
    // }

    
    return;
}