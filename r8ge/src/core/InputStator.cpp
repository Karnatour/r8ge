#include "../r8gepch.h"
#include "InputStator.h"


#include "events/MouseEvents.h"
#include "events/EventPayload.h"
#include "events/KeyEvents.h"

#include "Ar8ge.h"

namespace r8ge {
    InputStator::InputStator() : m_shiftPressed(false), m_ctrlPressed(false), m_altPressed(false),
                                 m_superPressed(false), m_poolFunction(nullptr) {
    }

    InputStator::~InputStator() = default;

    void InputStator::sendKeyAction(const Key &code, IOAction action) {
        if (code == Key::LEFT_SHIFT || code == Key::RIGHT_SHIFT) m_shiftPressed = (action == IOAction::PRESS);
        if (code == Key::LEFT_ALT || code == Key::RIGHT_ALT) m_altPressed = (action == IOAction::PRESS);
        if (code == Key::LEFT_CONTROL || code == Key::RIGHT_CONTROL) m_ctrlPressed = (action == IOAction::PRESS);
        if (code == Key::LEFT_SUPER || code == Key::RIGHT_SUPER) m_superPressed = (action == IOAction::PRESS);

        m_keyPressedMap[code] = (action == IOAction::PRESS);

        EventPayload payload;
        payload.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
        IOStroke stroke = {code, m_shiftPressed, m_ctrlPressed, m_altPressed, m_superPressed};
        if (action == IOAction::PRESS)
            payload.setEvent(std::make_shared<KeyPressed>(stroke, false));
        else
            payload.setEvent(std::make_shared<KeyReleased>(stroke));
        Ar8ge::getEventQueue()(payload);
    }

    void InputStator::sendMouseAction(const Key &code, IOAction action) {
        m_keyPressedMap[code] = (action == IOAction::PRESS);
        EventPayload payload;
        payload.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
        IOStroke stroke = {code, m_shiftPressed, m_ctrlPressed, m_altPressed, m_superPressed};
        if (action == IOAction::PRESS)
            payload.setEvent(std::make_shared<MousePressed>(stroke));
        else
            payload.setEvent(std::make_shared<MouseReleased>(stroke));
        Ar8ge::getEventQueue()(payload);
    }

    void InputStator::sendMousePos(const double &x, const double &y) {
        m_mousePos = std::make_pair(x, y);
        EventPayload payload;
        payload.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
        payload.setEvent(std::make_shared<MouseMoved>(x, y));
        Ar8ge::getEventQueue()(payload);
    }

    void InputStator::sendScrollPos(const double &x, const double &y) {
        m_scrollPos = std::make_pair(x, y);
        EventPayload payload;
        payload.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
        payload.setEvent(std::make_shared<MouseScrolled>(x, y));
        Ar8ge::getEventQueue()(payload);
    }

    std::function<void(const r8ge::Key &, IOAction)> InputStator::getMouseActionCallback() {
        return [this]<typename T0, typename T1>(T0 &&PH1, T1 &&PH2) {
            sendMouseAction(std::forward<T0>(PH1), std::forward<T1>(PH2));
        };
    }

    std::function<void(const double &, const double &)> InputStator::getMouseMovedCallback() {
        return [this]<typename T0, typename T1>(T0 &&PH1, T1 &&PH2) {
            sendMousePos(std::forward<T0>(PH1), std::forward<T1>(PH2));
        };
    }

    std::function<void(const double &, const double &)> InputStator::getScrollCallback() {
        return [this]<typename T0, typename T1>(T0 &&PH1, T1 &&PH2) {
            sendScrollPos(std::forward<T0>(PH1), std::forward<T1>(PH2));
        };
    }

    std::function<void(const r8ge::Key &, IOAction)> InputStator::getKeyActionCallback() {
        return [this]<typename T0, typename T1>(T0 &&PH1, T1 &&PH2) {
            sendKeyAction(std::forward<T0>(PH1), std::forward<T1>(PH2));
        };
    }

    bool InputStator::isShiftPressed() const {
        return m_shiftPressed;
    }

    bool InputStator::isCtrlPressed() const {
        return m_ctrlPressed;
    }

    bool InputStator::isAltPressed() const {
        return m_altPressed;
    }

    bool InputStator::isSuperPressed() const {
        return m_superPressed;
    }

    bool InputStator::isKeyPressed(const std::initializer_list<Key> &code, Modifier modifier) const {
        if (modifier & Modifier::SHIFT && !m_shiftPressed) return false;
        if (modifier & Modifier::CTRL && !m_ctrlPressed) return false;
        if (modifier & Modifier::ALT && !m_altPressed) return false;
        if (modifier & Modifier::SUPER && !m_superPressed) return false;
        return isKeyPressed(code);
    }

    bool InputStator::isKeyPressed(const std::initializer_list<Key> &code) const {
        for (auto &c: code) {
            if (c == Key::RIGHT_SHIFT || c == Key::LEFT_SHIFT || c == Key::RIGHT_CONTROL || c == Key::LEFT_CONTROL || c
                == Key::RIGHT_ALT || c == Key::LEFT_ALT || c == Key::RIGHT_SUPER || c == Key::LEFT_SUPER) {
                R8GE_LOG_WARNI("Invalid key code, use Modulator instead");
                return false;
            }
            {
                if (m_keyPressedMap.find(c) == m_keyPressedMap.end()) return false;
                if (!m_keyPressedMap.at(c)) return false;
            }
        }
        return true;
    }

    std::pair<double, double> InputStator::getMousePos() const {
        return m_mousePos;
    }

    std::pair<double, double> InputStator::getScrollPos() {
        std::pair<double,double> temp = m_scrollPos;
        m_scrollPos.second = 0;
        return temp;
    }
}
