#pragma once

#include <queue>
#include <thread>
#include <mutex>

#include "EventPayload.h"

namespace r8ge {
    // It's a queue of events that can be sent to the event system.
    // It's thread-safe. It's used by the Window class TODO: (for now just window class)
    // to send events to the event system. It's cleared by the ar8ge class.
    class EventQueue {
    public:
        // Callback function to the event queue system.
        using CallbackFn = std::function<void(const EventPayload&)>;

        EventQueue();
        ~EventQueue();

        // Send an event to the event queue, event is stored and then delegated
        // to the specified callback function.
        void sendEvent(const EventPayload& event);

        // Empty the queue, and delegate all the events to the callback function.
        void emptyQueue();

        // Callback function to engine event handler.
        void setEngineCallback(const std::function<void(const std::shared_ptr<Event>&)>& callback);

        // Get the callback function to the event queue system.
        [[nodiscard]] CallbackFn getCallbackFn();

    private:
        std::queue<EventPayload> m_queue;
        std::mutex m_queueMutex;
        std::function<void(const std::shared_ptr<Event>&)> m_engineCallback;
    };
}
