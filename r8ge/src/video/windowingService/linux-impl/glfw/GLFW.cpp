#include <GL/glew.h>

#include "GLFW.h"
#include <GLFW/glfw3.h>
#include "Convertor.h"
#include "../../../../core/events/EventPayload.h"
#include "../../../../core/Ar8ge.h"
#include "../../../../core/events/MouseEvents.h"
#include "../../../../core/events/WindowEvents.h"

#include <utility>

namespace r8ge {
    namespace video {
        std::shared_ptr<WindowingService> WindowingService::create() {
            return std::make_shared<GLFW>();
        }

        void GLFW::init() {
            glfwSetErrorCallback([](int error, const char *description) {
                R8GE_LOG_ERROR("GLFW Error: `{}`", description);
            });

            if (!glfwInit()) {
                R8GE_LOG_ERROR("Unable to init GLFW");
            }
            else {
                R8GE_LOG("GLFW Initialized running version `{}`", glfwGetVersionString());
            }

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
            glfwWindowHint(GLFW_DOUBLEBUFFER,true);
        }


        void GLFW::exit() {
            if (m_mainWindowCreated)
                destroyMainWindow();
            R8GE_LOG("GLFW windowing service released");
        }

        bool GLFW::createMainWindow(size_t width, size_t height, std::string title) {
            R8GE_LOG("GLFW Window is being creating `{}`", title);

            m_mainWindow = glfwCreateWindow(
                    static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);

            if (!m_mainWindow) {
                glfwTerminate();
                R8GE_LOG_ERROR("GLFW Main window `{}` failed to create", title);
                return false;
            }

            m_mainWindowCreated = true;
            m_mainWindowHeight = height;
            m_mainWindowWidth = width;

            R8GE_LOG_INFOR("GLFW Main window `{}` created", title.data());

            return true;
        }

        void GLFW::poolEvents() {
            glfwPollEvents();
        }

        void GLFW::setEventCallbacks() {
            if (!m_mainWindow) {
                R8GE_LOG_WARNI("Callbacks cannot be set, main Window is not created");
                return;
            }
            glfwSetWindowUserPointer(m_mainWindow, this);

            setResizeCallback([](int width, int height, r8ge::video::GLFrameBuffer& buffer) {
                buffer.rescaleFrameBuffer(width, height);
            });

            glfwSetKeyCallback(m_mainWindow, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    Key code = GLFWConvertor::convertKeyCode(key);

                    switch (action) {
                        case GLFW_PRESS:
                            instance->m_keyActionCallback(code, IOAction::PRESS);
                            R8GE_LOG("Pressed key {}", to_string(code));
                            break;
                        case GLFW_RELEASE:
                            instance->m_keyActionCallback(code, IOAction::RELEASE);
                            R8GE_LOG("Released key {}",to_string(code));
                            break;
                            /* TODO Add Repeat ??
                        case GLFW_REPEAT:
                            instance->m_keyActionCallback(code, IOAction::REPEAT);
                            break;
                             */
                        default:
                            break;
                    }

                }
            });

            glfwSetMouseButtonCallback(m_mainWindow, [](GLFWwindow *window, int button, int action, int mods) {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    Key code = GLFWConvertor::convertKeyCode(button);

                    switch (action) {
                        case GLFW_PRESS:
                            instance->m_keyActionCallback(code, IOAction::PRESS);
                            break;
                        case GLFW_RELEASE:
                            instance->m_keyActionCallback(code, IOAction::RELEASE);
                            break;
                        default:
                            break;
                    }
                }
            });

            glfwSetCursorPosCallback(m_mainWindow, [](GLFWwindow *window, double xpos, double ypos) {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    EventPayload p;
                    p.setEvent(std::make_shared<MouseMoved>(xpos, ypos));
                    p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                    Ar8ge::getEventQueue()(p);
                }
            });

            glfwSetScrollCallback(m_mainWindow, [](GLFWwindow *window, double xOffset, double yOffset) -> void {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    EventPayload p;
                    p.setEvent(std::make_shared<MouseScrolled>(xOffset, yOffset));
                    p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                    Ar8ge::getEventQueue()(p);
                }
            });

            glfwSetWindowSizeCallback(m_mainWindow, windowSizeCallback);

            glfwSetWindowCloseCallback(m_mainWindow, [](GLFWwindow *window) -> void {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    EventPayload p;
                    p.setEvent(std::make_shared<WindowClosed>());
                    p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                    Ar8ge::getEventQueue()(p);
                    R8GE_LOG("Window close event");
                }
            });

            glfwSetWindowFocusCallback(m_mainWindow, [](GLFWwindow *window, int focused) -> void {
                GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

                if (instance) {
                    EventPayload p;
                    if (focused) {
                        p.setEvent(std::make_shared<WindowFocus>());
                    }
                    else {
                        p.setEvent(std::make_shared<WindowLostFocus>());
                    }
                    p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                    Ar8ge::getEventQueue()(p);
                }
            });

            R8GE_LOG("Callbacks set successfully");
        }


        GLFW::~GLFW() {
            glfwTerminate();
        }

        bool GLFW::destroyMainWindow() {
            if (!m_mainWindowCreated) {
                return false;
            }
            glfwDestroyWindow(m_mainWindow);
            m_mainWindowCreated = false;
            R8GE_LOG("Main window has been destroyed");
            return true;
        }

        void GLFW::setContextOfMainWindow() {
            if (!m_mainWindowCreated)
                return;
            glfwMakeContextCurrent(m_mainWindow);
        }

        void GLFW::swapBuffersOfMainWindow() {
            if (!m_mainWindowCreated)
                return;
            glfwSwapBuffers(m_mainWindow);
        }

        void GLFW::windowSizeCallback(GLFWwindow *window, int width, int height) {
            GLFW *instance = static_cast<GLFW *>(glfwGetWindowUserPointer(window));

            if (instance) {
                instance->m_mainWindowWidth = width;
                instance->m_mainWindowHeight = height;

                glViewport(0, 0, width, height);
                if (instance->m_resizeCallback) {
                    instance->m_resizeCallback(width, height, *instance->m_frameBuffer);
                }

                EventPayload p;
                p.setEvent(std::make_shared<WindowResized>(width, height));
                p.setCallback(Ar8ge::getInstanceLayerSwitcherCallback());
                Ar8ge::getEventQueue()(p);
            }
        }

        bool GLFW::setGLContext() {
            if (!m_GLContextCreated) {
                glewInit();
                return true;
            }
            else {
                R8GE_LOG_WARNI("GL context already created");
                return false;
            }
        }

        GLFWwindow *GLFW::getWindow() {
            return m_mainWindow;
        }

        void GLFW::getFramebufferSize(int width, int height) {
            glfwGetFramebufferSize(m_mainWindow,&width,&height);
        }

        void GLFW::setViewport(int width,int height) {
            glViewport(0,0,width,height);
        }

        unsigned int GLFW::getWidth() {
            return m_mainWindowWidth;
        }

        unsigned int GLFW::getHeight() {
            return m_mainWindowHeight;
        }

        void GLFW::setVsync(bool state) {
            if (state) m_Vsync = true;
            if (!state) m_Vsync = false;
            glfwSwapInterval(state);
        }

        bool GLFW::getVsyncState(){
            return m_Vsync;
        }

        void GLFW::setResizeCallback(GLFW::ResizeCallback callback) {
            m_resizeCallback = std::move(callback);
        }

        void GLFW::setFrameBuffer(GLFrameBuffer &frameBuffer) {
            m_frameBuffer = &frameBuffer;
        }

    }
}