
#include "EventPayload.h"

namespace r8ge {
    EventPayload::EventCallbackFn EventPayload::getCallback() const {
        return m_callback;
    }

    void EventPayload::setCallback(const EventCallbackFn & cb) {
        m_callback = cb;
    }

    std::shared_ptr<Event> EventPayload::getEvent() const {
        return m_event;
    }

    void EventPayload::setEvent(const std::shared_ptr<Event> & e) {
        m_event = e;
    }

}