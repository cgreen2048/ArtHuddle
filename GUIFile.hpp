#ifndef __GUIFILE_HPP__
#define __GUIFILE_HPP__

#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "vec2.hpp"
#include "vec3.hpp"

const std::string LAYOUT_OPEN = "<layout>";
const std::string LAYOUT_CLOSE = "</layout>";
const std::string LINE_OPEN = "<line>";
const std::string LINE_CLOSE = "</line>";
const std::string BOX_OPEN = "<box>";
const std::string BOX_CLOSE = "</box>";
const std::string POINT_OPEN = "<point>";
const std::string POINT_CLOSE = "</point>";
const std::string VEC2_OPEN = "<vec2>";
const std::string VEC2_CLOSE = "</vec2>";
const std::string VEC3_OPEN = "<vec3>";
const std::string VEC3_CLOSE = "</vec3>";
const std::string IVEC2_OPEN = "<ivec2>";
const std::string IVEC2_CLOSE = "</ivec2>";
const std::string IVEC3_OPEN = "<ivec3>";
const std::string IVEC3_CLOSE = "</ivec3>";
const std::string X_OPEN = "<x>";
const std::string X_CLOSE = "</x>";
const std::string Y_OPEN = "<y>";
const std::string Y_CLOSE = "</y>";
const std::string Z_OPEN = "<z>";
const std::string Z_CLOSE = "</z>";

const std::vector<std::string> OPENERS = {LAYOUT_OPEN, LINE_OPEN, BOX_OPEN, POINT_OPEN, VEC2_OPEN, VEC3_OPEN, IVEC2_OPEN, IVEC3_OPEN, X_OPEN, Y_OPEN, Z_OPEN};
const std::vector<std::string> CLOSERS = {LAYOUT_CLOSE, LINE_CLOSE, BOX_CLOSE, POINT_CLOSE, VEC2_CLOSE, VEC3_CLOSE, IVEC2_CLOSE, IVEC3_CLOSE, X_CLOSE, Y_CLOSE, Z_CLOSE};

class GUIFile {
    public:
        struct {
                vec2 start;
                vec2 end;
                vec3 color;
            } typedef Line;

            struct {
                vec2 min;
                vec2 max;
                vec3 color;
            } typedef Box;

            struct {
                vec2 position;
                vec3 color;
            } typedef Point;

            GUIFile();
            const std::vector<Line>& getLines() const;
            const std::vector<Box>&  getBoxes() const;
            const std::vector<Point>& getPoints() const;
            void readFile(std::string);
            void writeFile(std::string);

        private:
            std::vector<Line> lines;
            std::vector<Box> boxes;
            std::vector<Point> points;
    
        // Line stores vec2, vec2, vec3
        

};

#endif
