#ifndef R8GE_ENGINEEVENTS_H
#define R8GE_ENGINEEVENTS_H

#include "../Core.h"

#include "Event.h"

namespace r8ge {
    struct EngineEvent : public Event {
        [[nodiscard]] Handler getHandler() const override;
    };

    struct EngineKill : public EngineEvent {
        EngineKill();
        static Type getEventType();
    };
}

#endif//!R8GE_ENGINEEVENTS_H
