#include "GameInstance.h"

#include "../../r8gepch.h"

#include "../Input.h"
#include "../Ar8ge.h"

namespace r8ge {
    GameInstance::GameInstance(std::string_view name) : m_name(name) {

    }

    std::string GameInstance::getGameName() const {
        return m_name;
    }

    void GameInstance::directEvent(const std::shared_ptr<Event> &event) {
        if(Input::isKeyPressed(Key::ESCAPE, Modifier::SHIFT)) {
            R8GE_LOG_DEBUG("Shift + Escape pressed, exiting");
            r8ge::Ar8ge::killEngine();
        }
    }
}