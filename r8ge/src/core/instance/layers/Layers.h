#pragma once

#include "../../Core.h"
#include "../../events/Event.h"
#include <string_view>

#include "../../TimeStep.h"


namespace r8ge {
    // One layer of Game/Editor/Sound Editor, used to separate the logic and rendering
    // This class should be defined by the user and registered in the GameInstance
    class Layer {
    public:
        explicit Layer(std::string_view name);
        virtual ~Layer();

        // Used to update the layer, called every frame
        virtual void update(TimeStep timestep) = 0;

        // Used to handle the events, called for every event that is delegated to the layer
        // if event is not handled, it will be delegated to the next layer, until its destroyed
        virtual void event(const std::shared_ptr<Event>& event) = 0;

        // Called by the render loop to render the layer
        virtual void render() = 0;


        [[nodiscard]] std::string getName() const;
    private:
        std::string m_name;
    };
}

