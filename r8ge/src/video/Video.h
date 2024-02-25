#ifndef R8GE_VIDEO_HH
#define R8GE_VIDEO_HH

#include "windowingService/WindowingService.h"
#include "renderingService/RenderingService.h"
#include "guiService/GUIService.h"
#include <memory>

namespace r8ge {
    class Video {
    public:
        Video();
        ~Video();

        void init();
        void run();
        void exit();

    private:
        std::string m_title;

    public:
        static std::shared_ptr<video::WindowingService> getWindowingService();
        static std::shared_ptr<video::RenderingService> getRenderingService();
        static std::shared_ptr<video::GUIService> getGUIService();

    private:
        static std::shared_ptr<video::WindowingService> s_windowingService;
        static std::shared_ptr<video::RenderingService> s_renderingService;
        static std::shared_ptr<video::GUIService> s_guiService;
        static bool s_isReady;
    };
}

#endif//!R8GE_VIDEO_HH
