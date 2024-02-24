#include "../../r8gepch.h"

#include "EngineEvents.h"

namespace r8ge {
    EngineKill::EngineKill() {
        m_header.type = Event::Type::KILL_ENGINE;
    }

    Event::Type EngineKill::getEventType() {
        return Event::Type::KILL_ENGINE;
    }

    Event::Handler EngineEvent::getHandler() const {
        return Handler::ENGINE;
    }
}


