#ifndef R8GE_VIDEO_HH
#define R8GE_VIDEO_HH

#include "windowingService/WindowingService.h"
#include "renderingService/RenderingService.h"
#include "guiService/GUIService.h"
#include "../core/TimeStep.h"
#include <memory>

namespace r8ge {
    class Video {
    public:
        Video();

        ~Video();

        void init();

        void run();

        void exit();

        static std::shared_ptr<video::WindowingService> getWindowingService();

        static std::shared_ptr<video::RenderingService> getRenderingService();

        static std::shared_ptr<video::GUIService> getGUIService();

        static std::shared_ptr<TimeStep> getTimeStep();

        static bool m_firstFrameLoop;

        static bool m_editorMode;

    private:
        static std::shared_ptr<video::WindowingService> s_windowingService;
        static std::shared_ptr<video::RenderingService> s_renderingService;
        static std::shared_ptr<video::GUIService> s_guiService;
        static std::shared_ptr<TimeStep> s_timestep;
        double m_lastFrameRenderTime = 0;
        std::string m_title;
    };
}

#endif//!R8GE_VIDEO_HH
