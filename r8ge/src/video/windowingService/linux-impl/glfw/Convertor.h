#ifndef R8GE_CONVERTOR_H
#define R8GE_CONVERTOR_H

#include <GLFW/glfw3.h>
#include "../../../../core/events/Strokes.h"

namespace r8ge {
    namespace video {
        class GLFWConvertor {
        public:
            static Key convertKeyCode(int glfwKeyCode);
        };
    }
}

#endif//!R8GE_GLFW_CONVERTOR_H
