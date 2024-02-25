#pragma once

#include <memory>
#include <functional>

#include "Event.h"

namespace r8ge {
    namespace event {
        class Dispatcher {
        public:
            Dispatcher(const std::shared_ptr<Event>& event) ;
            ~Dispatcher();

            template<typename T>
            requires std::is_base_of<Event, T>::value
            void dispatch(const std::function<bool(const std::shared_ptr<T>&)>& fun) {
                if(T::getEventType() == m_event->getType())
                if(!m_event->isHandled())
                if (fun(std::dynamic_pointer_cast<T>(m_event)))
                    m_event->setToHandled();
            }
        private:
            std::shared_ptr<Event> m_event;
        };

    }
}
