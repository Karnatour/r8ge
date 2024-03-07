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
        void sendMousePos(const double &x, const double &y);
        void sendScrollPos(const double &x, const double &y);

        [[nodiscard]] std::function<void(const r8ge::Key&, IOAction)> getKeyActionCallback();
        [[nodiscard]] std::function<void(const r8ge::Key&, IOAction)> getMouseActionCallback();
        [[nodiscard]] std::function<void(const double&, const double&)> getMouseMovedCallback();
        [[nodiscard]] std::function<void(const double&, const double&)> getScrollCallback();

        [[nodiscard]] bool isShiftPressed() const;
        [[nodiscard]] bool isCtrlPressed() const;
        [[nodiscard]] bool isAltPressed() const;
        [[nodiscard]] bool isSuperPressed() const;

        // Returns true if all keys in the list are pressed and the modulator is satisfied
        // F.e. isKeyPressed({IOCode::A, IOCode::B}, video::Input::Shift | video::Input::Ctrl) returns true if A and B are pressed and Shift and Ctrl are pressed
        [[nodiscard]] bool isKeyPressed(const std::initializer_list<Key>& code, Modifier modifier) const;
        [[nodiscard]] bool isKeyPressed(const std::initializer_list<Key>& code) const;

        [[nodiscard]] std::pair<double, double> getMousePos() const;
        [[nodiscard]] std::pair<double, double> getScrollPos();

    private:
        std::unordered_map<r8ge::Key,bool> m_keyPressedMap;
        std::pair<double,double> m_mousePos,m_scrollPos;
        std::function<void(void)> m_poolFunction;

        bool m_shiftPressed;
        bool m_ctrlPressed;
        bool m_altPressed;
        bool m_superPressed;
    };
}

