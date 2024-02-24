
#include "Event.h"

namespace r8ge {
    Event::Event() {
        m_header.type = Type::NONE;
        m_header.handled = false;
    }

    Event::~Event() = default;

    Event::Type Event::getType() const {
        return m_header.type;
    }

    bool Event::isHandled() const {
        return m_header.handled;
    }

    void Event::setToHandled() {
        m_header.handled = true;
    }

    std::string Event::to_string() const {
        switch (m_header.type) {
            case Type::NONE:               return "NONE";
            case Type::WINDOW_RESIZED:     return "WINDOW_RESIZED";
            case Type::WINDOW_CLOSED:      return "WINDOW_CLOSED";
            case Type::WINDOW_FOCUS:       return "WINDOW_FOCUS";
            case Type::WINDOW_LOST_FOCUS:  return "WINDOW_LOST_FOCUS";
            case Type::KEY_PRESSED:        return "KEY_PRESSED";
            case Type::KEY_RELEASED:       return "KEY_RELEASED";
            case Type::MOUSE_PRESSED:      return "MOUSE_PRESSED";
            case Type::MOUSE_RELEASED:     return "MOUSE_RELEASED";
            case Type::MOUSE_MOVED:        return "MOUSE_MOVED";
            case Type::MOUSE_SCROLLED:     return "MOUSE_SCROLLED";
            case Type::KILL_ENGINE:        return "KILL_ENGINE";
        }
        return "";
    }

    Event::Handler Event::getHandler() const {
        return Event::Handler::NONE;
    }

    Event::Handler UserEvent::getHandler() const {
        return Event::Handler::USER;
    }
}