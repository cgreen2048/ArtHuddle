#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "GuiElement.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Box.hpp"

extern GuiElement* factory(guiElement);


// template <typename... Args>
// GuiElement* factory(guiElement e, Args&&... args) {
// 	if (sizeof...(args) == 2) {
//         switch (e) {
//             case guiElement::POINT: {
//                 return new Point(std::forward<Args>(args)...);
//             }
//             default: {
//                 return nullptr;
//             }
//         }
//     }
//     else if (sizeof...(args) == 3) {
//         switch (e) {
//             case guiElement::LINE: {
//                 return new Line(std::forward<Args>(args)...);
//             }
//             case guiElement::BOX: {
//                 return new Box(std::forward<Args>(args)...);
//             }
//             default: {
//                 return nullptr;
//             }
//         }
//     }
    
    
//     // switch (e) {
//     //     case guiElement::POINT: {
//     //         return new Point(std::forward<Args>(args)...);
// 	// 	}
// 	// 	case guiElement::LINE: {
//     //         return new Line(std::forward<Args>(args)...);
// 	// 	}
// 	// 	case guiElement::BOX: {
// 	// 		return new Box(std::forward<Args>(args)...);
// 	// 	}
// 	// }
// 	return nullptr;
// }

#endif
