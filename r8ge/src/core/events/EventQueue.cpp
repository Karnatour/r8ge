
#include "EventQueue.h"

#include <functional>
#include "../Logger.h"

namespace r8ge {


    EventQueue::EventQueue() : m_queue{}, m_queueMutex{}, m_engineCallback([](const std::shared_ptr<Event>&) {
        R8GE_LOG_WARNI("EventQueue::EventQueue() - Engine callback not set!");
    }) {}

    void EventQueue::sendEvent(const EventPayload &event) {
        m_queueMutex.lock();
        m_queue.push(event);
        m_queueMutex.unlock();
    }

    void EventQueue::emptyQueue() {
        m_queueMutex.lock();
        while(!m_queue.empty())
        {
            auto& eventP = m_queue.front();
            if(eventP.getEvent()->getHandler() == Event::Handler::USER)
                eventP.getCallback()(eventP.getEvent());
            else if(eventP.getEvent()->getHandler() == Event::Handler::ENGINE)
            {
                m_engineCallback(eventP.getEvent());
            }
            m_queue.pop();
        }
        m_queueMutex.unlock();
    }

    EventQueue::CallbackFn EventQueue::getCallbackFn() {
        return [this](auto && p) { sendEvent(std::forward<decltype(p)>(p)); };
    }

    EventQueue::~EventQueue() {
        emptyQueue();
    }

    void EventQueue::setEngineCallback(const std::function<void(const std::shared_ptr<Event> &)> &callback) {
        m_engineCallback = callback;
    }
}