#include "Dispatcher.h"

namespace r8ge {

    event::Dispatcher::Dispatcher(const std::shared_ptr<Event> &event) : m_event(event) {

    }

    event::Dispatcher::~Dispatcher() = default;
}