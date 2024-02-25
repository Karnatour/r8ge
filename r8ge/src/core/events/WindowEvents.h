#pragma once

#include "Event.h"

namespace r8ge {
    struct WindowResized : public UserEvent
    {
        unsigned int x, y;

        WindowResized(unsigned int _x, unsigned int _y);
        static Type getEventType();
    };

    struct WindowClosed : public UserEvent
    {
        WindowClosed();
        static Type getEventType();
    };

    struct WindowFocus : public UserEvent
    {
        WindowFocus();
        static Type getEventType();
    };

    struct WindowLostFocus : public UserEvent
    {
        WindowLostFocus();
        static Type getEventType();
    };
}
