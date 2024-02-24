#pragma once

#include "Instance.h"

namespace r8ge {

    // The main game instance, handles the layers, and the logic,
    // TODO: for now, there can be only one instance of the game, this will be changed in the future
    class  GameInstance : public Instance {
    public:
        explicit GameInstance(std::string_view name);
        virtual ~GameInstance() override = default;

        [[nodiscard]] std::string getGameName() const;

        void directEvent(const std::shared_ptr<Event> &event) override;
    private:
        std::string m_name;
    };
}
