#include "WindowEvents.h"

namespace r8ge {

    WindowResized::WindowResized(unsigned int _x, unsigned int _y) :x(_x),y(_y) {
        m_header.type = Event::Type::WINDOW_RESIZED;
    }

    Event::Type WindowResized::getEventType() {
        return Event::Type::WINDOW_RESIZED;;
    }

    WindowClosed::WindowClosed() {
        m_header.type = Event::Type::WINDOW_CLOSED;
    }

    Event::Type WindowClosed::getEventType() {
        return Event::Type::WINDOW_CLOSED;;
    }

    WindowFocus::WindowFocus() {
        m_header.type = Event::Type::WINDOW_FOCUS;
    }

    Event::Type WindowFocus::getEventType() {
        return Event::Type::WINDOW_FOCUS;
    }

    WindowLostFocus::WindowLostFocus() {
        m_header.type = Event::Type::WINDOW_LOST_FOCUS;
    }

    Event::Type WindowLostFocus::getEventType() {
        return Event::Type::WINDOW_LOST_FOCUS;
    }
}
