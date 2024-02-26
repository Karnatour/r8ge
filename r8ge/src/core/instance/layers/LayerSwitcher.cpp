#include "LayerSwitcher.h"

#include <algorithm>
#include <sstream>
#include <ranges>

#include "../../Logger.h"

namespace r8ge {

    void LayerSwitcher::pushFront(const std::shared_ptr<Layer> &l) {
        m_layers.push_back(l);

        R8GE_LOG("Layer `{}` added to LayerSwitcher [{}]", l->getName(), to_string());
    }

    void LayerSwitcher::pushBack(const std::shared_ptr<Layer> &l) {
        pushFront(l);
        std::rotate(m_layers.rbegin(), m_layers.rbegin() + 1, m_layers.rend());
    }

    void LayerSwitcher::pop(std::string_view name) {
        for(auto[i, l] : m_layers | std::views::enumerate)
        {
            if(l->getName()==name)
            {
                pop(i);
                return;
            }
        }
    }

    void LayerSwitcher::pop(size_t index) {
        m_layers.erase(m_layers.begin()+index);
    }

    void LayerSwitcher::popFront() {
        m_layers.pop_back();
    }

    void LayerSwitcher::popBack() {
        m_layers.erase(m_layers.begin());
    }

    void LayerSwitcher::sendEvent(const std::shared_ptr<Event> &e) const {
        for(size_t i = m_layers.size(); i > 0; --i)
        {
            if(!e->isHandled())
                m_layers[i-1]->event(e);
            else // TODO: If so handled - log to event_log_handled file
                return;
        }

        /*
        if(!e->isHandled())
        R8GE_LOG("Event `{}` was not handled", e->to_string()); // TODO: log to event_log_unhandled file
         */
    }

    void LayerSwitcher::updateAll(TimeStep timestep) const {
        for(auto& l : m_layers)
            l->update(timestep);
    }

    void LayerSwitcher::renderAll() const {
        for(auto& l : m_layers)
            l->render();
    }

    LayerSwitcher::LayerSwitcher() : m_layers{}{}

    std::string LayerSwitcher::to_string() const {
        std::stringstream ss;

        for(auto[i, l] : m_layers | std::views::enumerate)
            ss << l->getName()  << "[" << i << "]" << "<-";
        ss << "@";
        return ss.str();
    }
}