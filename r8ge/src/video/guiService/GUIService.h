#ifndef R8GE_GUISERVICE_H
#define R8GE_GUISERVICE_H

#include <memory>
#include "../windowingService/WindowingService.h"
#include "../renderingService/openGL/GLFrameBuffer.h"
#include "../renderer/Scene.h"


namespace r8ge {
    namespace video {
        class GUIService {
        public:
            GUIService();

            virtual ~GUIService() = default;

            virtual void init(WindowingService &service) = 0;

            virtual void exit() = 0;

            virtual void beginFrame() = 0;

            //TODO Replace this with rendering service after merging GLFramebuffer into GLService
            virtual void render(GLFrameBuffer &frameBuffer,Scene &scene) = 0;

            virtual void endFrame(WindowingService &service) = 0;

            virtual void insertSceneIntoSceneItems(Scene &scene) = 0;

            virtual void showDemoWindow() = 0;

            static std::shared_ptr<GUIService> create();

        protected:
            bool m_isInitialized;
        };
    } // r8ge
} // video

#endif //R8GE_GUISERVICE_H
