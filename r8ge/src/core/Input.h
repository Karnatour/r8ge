#pragma once

#include "Core.h"
#include "InputStator.h"

namespace r8ge {
    class Input {
    public:
        [[nodiscard]] static bool isKeyPressed(Key code, Modifier mod = Modifier::NONE);
        [[nodiscard]] static bool isKeyPressed(const std::initializer_list<Key>& code, Modifier mod = Modifier::NONE);

        [[nodiscard]] static bool isShiftPressed();
        [[nodiscard]] static bool isCtrlPressed();
        [[nodiscard]] static bool isAltPressed();
        [[nodiscard]] static bool isSuperPressed();

        [[nodiscard]] static std::function<void(const r8ge::Key&, IOAction)> getKeyActionCallback();
        [[nodiscard]] static std::function<void(const r8ge::Key&, IOAction)> getMouseActionCallback();

        static void setInstance(const std::shared_ptr<InputStator>& input);
    private:
        static std::shared_ptr<InputStator> s_input;
        static std::mutex s_mutex;
    };
}

