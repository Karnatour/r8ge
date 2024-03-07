#include "WindowingService.h"

#include <r8ge/r8ge.h>

namespace r8ge {
    namespace video {
        WindowingService::WindowingService() : m_mainWindowCreated(false) {}
        WindowingService::~WindowingService() = default;

        void WindowingService::setKeyPressedCallback(std::function<void(const r8ge::Key &, IOAction)> callback) {
            m_keyActionCallback = callback;
        }

        void WindowingService::setMousePressedCallback(std::function<void(const r8ge::Key &, IOAction)> callback) {
            m_mouseActionCallback = callback;
        }

        void WindowingService::setMousePosCallback(std::function<void(const double &, const double & )> callback) {
            m_mouseMoveCallback = callback;
        }

        void WindowingService::setScrollCallback(std::function<void(const double &, const double &)> callback) {
            m_scrollCallback = callback;
        }
    }
}