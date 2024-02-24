#pragma once

#include "Core.h"
#include "events/Strokes.h"

namespace r8ge {
    class InputStator {
    public:
        InputStator();
        ~InputStator();

        void sendKeyAction(const r8ge::Key &code, IOAction action);
        void sendMouseAction(const r8ge::Key &code, IOAction action);

        [[nodiscard]] std::function<void(const r8ge::Key&, IOAction)> getKeyActionCallback();
        [[nodiscard]] std::function<void(const r8ge::Key&, IOAction)> getMouseActionCallback();

        bool isShiftPressed() const;
        bool isCtrlPressed() const;
        bool isAltPressed() const;
        bool isSuperPressed() const;

        // Returns true if all keys in the list are pressed and the modulator is satisfied
        // F.e. isKeyPressed({IOCode::A, IOCode::B}, video::Input::Shift | video::Input::Ctrl) returns true if A and B are pressed and Shift and Ctrl are pressed
        bool isKeyPressed(const std::initializer_list<Key>& code, Modifier modifier) const;
        bool isKeyPressed(const std::initializer_list<Key>& code) const;
    private:
        std::unordered_map<r8ge::Key,bool> m_keyPressedMap;
        std::function<void(void)> m_poolFunction;

        bool m_shiftPressed : 1;
        bool m_ctrlPressed : 1;
        bool m_altPressed : 1;
        bool m_superPressed : 1;
    };
}

