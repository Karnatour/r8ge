#pragma once

#include "Event.h"
#include "Strokes.h"

namespace r8ge {
    struct MouseMoved : public UserEvent
    {
        double x, y;

        MouseMoved(double _x, double _y);
        static Type getEventType();
    };

    struct MouseScrolled : public UserEvent
    {
        double x, y;

        MouseScrolled(double _x, double _y);
        static Type getEventType();
    };

    struct MousePressed : public UserEvent
    {
        IOStroke stroke;

        explicit MousePressed(IOStroke _stroke);
        static Type getEventType();
    };

    struct MouseReleased : public UserEvent
    {
        IOStroke stroke;

        explicit MouseReleased(IOStroke _stroke);
        static Type getEventType();
    };
}
