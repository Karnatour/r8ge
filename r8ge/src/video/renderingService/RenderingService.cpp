#include "RenderingService.h"

#include "openGL/GLService.h"

#include <memory>

namespace r8ge {
    namespace video {
        RenderingService::RenderingService() : m_clearColor({0,0,0.5,1}){}
        RenderingService::~RenderingService() = default;
        std::shared_ptr<RenderingService> RenderingService::create(RenderingService::API api) {
            switch (api) {
                case RenderingService::API::OpenGL:  return std::make_shared<GLService>();
                default: return nullptr;
            }
        }

        unsigned int RenderingService::id = 0;

        void RenderingService::setClearColor(ColorRGBA c) {
            m_clearColor = c;
        }
    }
}