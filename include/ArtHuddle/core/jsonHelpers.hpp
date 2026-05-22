#ifndef __JSON_HELPERS_HPP__
#define __JSON_HELPERS_HPP__

#include "../external/JsonDefinition.hpp"
#include "ArtHuddle/core/ElementTypes.hpp"
#include "ArtHuddle/core/ElementParameters.hpp"
#include "ArtHuddle/core/vec2.hpp"
#include "ArtHuddle/core/vec3.hpp"

inline json elementParametersToJson(ElementParameters ep) {
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

inline ElementParameters jsonToElementParameters(const json& j) {
    ElementParameters ep;

    ep.name = j.at("name").get<std::string>();
    ep.elementType = static_cast<guiElement>(j.at("elementType").get<int>());
    ep.color = j.at("color").get<ivec3>();

    switch (ep.elementType) {
        case guiElement::POINT: {
            ep.coords = j.at("coords").get<ivec2>();
            ep.coordsType = static_cast<TagType>(j.at("coordsType").get<int>());
            break;
        }
        case guiElement::LINE: {
            ep.start = j.at("start").get<ivec2>();
            ep.end = j.at("end").get<ivec2>();
            ep.startType = static_cast<TagType>(j.at("startType").get<int>());
            ep.endType = static_cast<TagType>(j.at("endType").get<int>());
            break;
        }
        case guiElement::BOX: {
            ep.min = j.at("min").get<ivec2>();
            ep.max = j.at("max").get<ivec2>();
            ep.minType = static_cast<TagType>(j.at("minType").get<int>());
            ep.maxType = static_cast<TagType>(j.at("maxType").get<int>());
            break;
        }
        case guiElement::TRIANGLE: {
            ep.pointA = j.at("pointA").get<ivec2>();
            ep.pointB = j.at("pointB").get<ivec2>();
            ep.pointC = j.at("pointC").get<ivec2>();
            ep.pointAType = static_cast<TagType>(j.at("pointAType").get<int>());
            ep.pointBType = static_cast<TagType>(j.at("pointBType").get<int>());
            ep.pointCType = static_cast<TagType>(j.at("pointCType").get<int>());
            break;
        }
        case guiElement::ELLIPSE: {
            ep.center = j.at("center").get<ivec2>();
            ep.radiusX = j.at("radiusX").get<int>();
            ep.radiusY = j.at("radiusY").get<int>();
            ep.centerType = static_cast<TagType>(j.at("centerType").get<int>());
            break;
        }
        case guiElement::ARROW: {
            ep.min = j.at("min").get<ivec2>();
            ep.max = j.at("max").get<ivec2>();
            ep.minType = static_cast<TagType>(j.at("minType").get<int>());
            ep.maxType = static_cast<TagType>(j.at("maxType").get<int>());

            ep.pointA = j.at("pointA").get<ivec2>();
            ep.pointB = j.at("pointB").get<ivec2>();
            ep.pointC = j.at("pointC").get<ivec2>();
            ep.pointAType = static_cast<TagType>(j.at("pointAType").get<int>());
            ep.pointBType = static_cast<TagType>(j.at("pointBType").get<int>());
            ep.pointCType = static_cast<TagType>(j.at("pointCType").get<int>());
            break;
        }
        case guiElement::TEXTBOX: {
            ep.min = j.at("min").get<ivec2>();
            ep.max = j.at("max").get<ivec2>();
            ep.minType = static_cast<TagType>(j.at("minType").get<int>());
            ep.maxType = static_cast<TagType>(j.at("maxType").get<int>());
            ep.textColor = j.at("textColor").get<ivec3>();
            ep.text = j.at("text").get<std::string>();
            break;
        }
        case guiElement::FREEHAND: {
            ep.points.clear();
            for (const auto& p : j.at("points")) {
                ep.points.push_back(p.get<ivec2>());
            }

            ep.hasFirstPoint = j.at("hasFirstPoint").get<bool>();
            ep.lastDrawnPoint = j.at("lastDrawnPoint").get<ivec2>();
            ep.finished = j.at("finished").get<bool>();
            ep.isFreehandShape = j.at("isFreehandShape").get<bool>();
            ep.minBound = j.at("minBound").get<ivec2>();
            ep.maxBound = j.at("maxBound").get<ivec2>();
            break;
        }
        default: {
            break;
        }
    }

    return ep;
}

#endif

