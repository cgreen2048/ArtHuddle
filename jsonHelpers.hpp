#include "./external/JsonDefinition.hpp"
#include "ElementParameters.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

json elementParametersToJson(ElementParameters ep) {
    json j;
    j["name"] = ep.name;
    j["elementType"] = ep.elementType;
    j["color"] = ep.color;
    
    switch (ep.elementType) {
        case guiElement::POINT: {
            j["coords"] = ep.coords;
            j["coordsType"] = static_cast<int>(ep.coordsType);
            break;
        }
        case guiElement::LINE: {
            j["start"] = ep.start;
            j["end"] = ep.end;
            j["startType"] = static_cast<int>(ep.startType);
            j["endType"] = static_cast<int>(ep.endType);
            break;
        }
        case guiElement::BOX: {
            j["min"] = ep.min;
            j["max"] = ep.max;
            j["minType"] = static_cast<int>(ep.minType);
            j["maxType"] = static_cast<int>(ep.maxType);
            break;
        }
        case guiElement::TRIANGLE: {
            j["pointA"] = ep.pointA;
            j["pointB"] = ep.pointB;
            j["pointC"] = ep.pointC;
            j["pointAType"] = static_cast<int>(ep.pointAType);
            j["pointBType"] = static_cast<int>(ep.pointBType);
            j["pointCType"] = static_cast<int>(ep.pointCType);
            break;
        }
        case guiElement::ELLIPSE: {
            j["center"] = ep.center;
            j["radiusX"] = ep.radiusX;
            j["radiusY"] = ep.radiusY;
            j["centerType"] = static_cast<int>(ep.centerType);
            break;
        }
        case guiElement::ARROW: {
            j["min"] = ep.min;
            j["max"] = ep.max;
            j["minType"] = static_cast<int>(ep.minType);
            j["maxType"] = static_cast<int>(ep.maxType);
            j["pointA"] = ep.pointA;
            j["pointB"] = ep.pointB;
            j["pointC"] = ep.pointC;
            j["pointAType"] = static_cast<int>(ep.pointAType);
            j["pointBType"] = static_cast<int>(ep.pointBType);
            j["pointCType"] = static_cast<int>(ep.pointCType);
            break;
        }
        case guiElement::TEXTBOX: {
            j["min"] = ep.min;
            j["max"] = ep.max;
            j["minType"] = static_cast<int>(ep.minType);
            j["maxType"] = static_cast<int>(ep.maxType);
            j["textColor"] = ep.textColor;
            j["text"] = ep.text;
            break;
        }
        case guiElement::FREEHAND: {
            j["points"] = json::array();
            for (auto& p : ep.points) {
                j["points"].push_back(p);
            }
            j["hasFirstPoint"] = ep.hasFirstPoint;
            j["lastDrawnPoint"] = ep.lastDrawnPoint;
            j["finished"] = ep.finished;
            j["isFreehandShape"] = ep.isFreehandShape;
            j["minBound"] = ep.minBound;
            j["maxBound"] = ep.maxBound;
            break;
        }
        default: {
            break;
        }
    }
    
    return j;
}

