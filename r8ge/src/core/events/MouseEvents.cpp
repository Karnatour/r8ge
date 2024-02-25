#include "../../r8gepch.h"

#include "MouseEvents.h"

namespace r8ge {

    MouseMoved::MouseMoved(double _x, double _y) : x(_x), y(_y) {
        m_header.type = Type::MOUSE_MOVED;
    }

    Event::Type MouseMoved::getEventType() {
        return Type::MOUSE_MOVED;
    }

    MouseScrolled::MouseScrolled(double _x, double _y) : x(_x),y(_y) {
        m_header.type = Type::MOUSE_SCROLLED;
    }

    Event::Type MouseScrolled::getEventType() {
        return Type::MOUSE_SCROLLED;
    }

    MousePressed::MousePressed(IOStroke _stroke) : stroke(_stroke) {
        m_header.type = Type::MOUSE_PRESSED;
    }

    Event::Type MousePressed::getEventType() {
        return Type::MOUSE_PRESSED;
    }

    MouseReleased::MouseReleased(IOStroke _stroke) : stroke(_stroke) {
        m_header.type = Type::MOUSE_RELEASED;
    }

    Event::Type MouseReleased::getEventType() {
        return Type::MOUSE_RELEASED;
    }
}
