#ifndef R8GE_GLFW_H
#define R8GE_GLFW_H


#include "../../WindowingService.h"
#include "../../../renderingService/openGL/GLFrameBuffer.h"


namespace r8ge {
    namespace video {
        class GLFW : public WindowingService {
        public:
            ~GLFW() override;

            void init() override;

            void exit() override;

            bool createMainWindow(size_t width, size_t height, std::string title) override;

            void poolEvents() override;

            bool destroyMainWindow() override;

            void setEventCallbacks() override;

            bool setGLContext() override;

            void setContextOfMainWindow() override;

            void swapBuffersOfMainWindow() override;

            GLFWwindow *getWindow() override;

            void getFramebufferSize(int width, int height) override;

            void setViewport(int width, int height) override;

            unsigned int getWidth() override;

            unsigned int getHeight() override;

            void setVsync(bool state) override;

            bool getVsyncState() override;

            static void windowSizeCallback(GLFWwindow *window, int width, int height);

            void setResizeCallback(ResizeCallback callback);

            void setFrameBuffer(r8ge::video::GLFrameBuffer& frameBuffer) override;

        private:
            size_t m_mainWindowWidth, m_mainWindowHeight;
            std::string m_mainWindowTitle;
            bool m_Vsync = false;
            GLFWwindow *m_mainWindow;
            r8ge::video::GLFrameBuffer* m_frameBuffer = nullptr;
            ResizeCallback m_resizeCallback;
        };
    }
}

#endif//!R8GE_GLFW_H
