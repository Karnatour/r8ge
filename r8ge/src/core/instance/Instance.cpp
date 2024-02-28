#include "Instance.h"

namespace r8ge {
    Instance::Instance() : m_layerSwitecher() {}
    Instance::~Instance() = default;

    void Instance::eventReceiver(const std::shared_ptr<Event>& event) {
        directEvent(event);
        m_layerSwitecher.sendEvent(event);
    }

    void Instance::update() {
        m_layerSwitecher.updateAll();
        m_layerSwitecher.renderAll();

    }

    LayerSwitcher &Instance::layerSwitcher() {
        return m_layerSwitecher;
    }

    std::function<void(const std::shared_ptr<Event> &)> Instance::getEventReceiver() {
        return [this](auto && PH1) { eventReceiver(std::forward<decltype(PH1)>(PH1)); };
    }
}
