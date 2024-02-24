#include "../r8gepch.h"
#include "Input.h"

namespace r8ge {

    std::shared_ptr<InputStator> Input::s_input = nullptr;
    std::mutex Input::s_mutex;

    bool Input::isKeyPressed(Key code, Modifier mod) {
        return s_input->isKeyPressed({code}, mod);
    }

    bool Input::isKeyPressed(const std::initializer_list<Key> &code, Modifier mod) {
        return s_input->isKeyPressed(code, mod);
    }

    bool Input::isShiftPressed() {
        return s_input->isShiftPressed();
    }

    bool Input::isCtrlPressed() {
        return s_input->isCtrlPressed();
    }

    bool Input::isAltPressed() {
        return s_input->isAltPressed();
    }

    bool Input::isSuperPressed() {
        return s_input->isSuperPressed();
    }

    std::function<void(const r8ge::Key &, IOAction)> Input::getKeyActionCallback() {
        return s_input->getKeyActionCallback();
    }

    std::function<void(const r8ge::Key &, IOAction)> Input::getMouseActionCallback() {
        return s_input->getMouseActionCallback();
    }

    void Input::setInstance(const std::shared_ptr<InputStator>& input) {
        s_input = input;
    }
}