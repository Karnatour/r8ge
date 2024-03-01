#pragma once

#include <vector>
#include <concepts>

#include "Layers.h"

namespace r8ge {
    // Handles the layers, and the events to the layers
    // Is in the Instance class.
    // Event workflow:
    //       EventReceiver
    //           |
    //           v
    //       LayerSwitcher
    //           |
    //           v
    //       Layer[n] -> Layer[n-1] -> ... -> Layer[0]
    //
    // Update and Render workflow:
    //       UpdateAll / RenderAll
    //                 |
    //                 v
    //       Layer[0] -> Layer[1] -> ... -> Layer[n]
    class LayerSwitcher final {
    public:
        LayerSwitcher();

        // Pushes the layer to the front - first layer to receive the event, and the last to render
        void pushFront(const std::shared_ptr<Layer>& l);

        // Pushes the layer to the back - last layer to receive the event, and the first to render
        void pushBack(const std::shared_ptr<Layer>& l);

        // Pushes the layer to the front - first layer to receive the event, and the last to render
        template <typename T>
        void add () {
            pushFront(std::make_shared<T>());
        }

        // Pop according to the name
        void pop(std::string_view name);

        // Pop according to the index
        inline void pop(size_t index);

        // Pop the first layer - first layer to receive the event, and the last to render
        inline void popFront();

        // Pop the last layer - last layer to receive the event, and the first to render
        inline void popBack();

        // Sends the event to the layers
        // The event is sent to the layers from the last to the first
        // layer[n] -> layer[n-1] -> ... -> layer[0]
        void sendEvent(const std::shared_ptr<Event>& e) const;

        // Updates all the layers, starting from the most bottom layer; layer[0] -> layer[n]
        void updateAll() const;

        // Renders all the layers, starting from the most bottom layer; layer[0] -> layer[n]
        void renderAll() const;

        // Returns the string representation of the LayerSwitcher
        [[nodiscard]] std::string to_string() const;
    private:
        std::vector<std::shared_ptr<Layer>> m_layers;
    };
}
