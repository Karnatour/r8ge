#pragma once

#include <functional>
#include <memory>

#include "Event.h"

namespace r8ge {

    // Used to store the event and the callback function, callback function has to lead to the specific
    // instance, then to specific layers
    class EventPayload {
        // Callback function to the final destination
        using EventCallbackFn = std::function<void(std::shared_ptr<Event> const&)>;
    public:

        // Callback function to the final destination
        [[nodiscard]] EventCallbackFn getCallback() const;

        // Set the callback function to the final destination
        void setCallback(const EventCallbackFn&);

        // Get the event, that is stored in the payload
        [[nodiscard]] std::shared_ptr<Event> getEvent() const;

        // Set the event, to be stored in the payload
        void setEvent(std::shared_ptr<Event> const&);
    private:
        std::shared_ptr<Event> m_event;
        EventCallbackFn m_callback;
    };
}
