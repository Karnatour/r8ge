#include "KeyEvents.h"

namespace r8ge {
    KeyPressed::KeyPressed(IOStroke _key, bool _repeat) : repeat(_repeat), stroke(_key) {
        m_header.type = Type::KEY_PRESSED;
    }

    Event::Type KeyPressed::getEventType() {
        return Event::Type::KEY_PRESSED;
    }

    KeyReleased::KeyReleased(IOStroke _key) : stroke(_key) {
        m_header.type = Type::KEY_RELEASED;
    }

    Event::Type KeyReleased::getEventType() {
        return Event::Type::KEY_RELEASED;
    }
}
