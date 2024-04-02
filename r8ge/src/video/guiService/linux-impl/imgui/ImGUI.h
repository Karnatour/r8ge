//
// Created by karnatour on 15.1.24.
//

#ifndef R8GE_IMGUI_H
#define R8GE_IMGUI_H

#include "../../GUIService.h"
#include "../../../windowingService/WindowingService.h"
#include "../../../renderingService/openGL/GLTexture.h"
#include <imgui.h>
#include <imgui_internal.h>

#include "ImGuizmo.h"


namespace r8ge {
    namespace video {
        class ImGUI : public GUIService{
        public:
            ~ImGUI() override;

            void init(WindowingService &service) override;

            void exit() override;

            void beginFrame() override;

            void renderEditorUI(r8ge::video::GLFrameBuffer &frameBuffer, Scene &scene) override;

            void endFrame(WindowingService &service) override;

            void insertSceneIntoSceneItems(Scene &scene) override;

            float getViewportWidth() override;

            float getViewportHeight() override;

            float getViewportPosX() override;

            float getViewportPosY() override;

            void renderR8GELayout();

            void setColors();

            void showDemoWindow() override;

        private:
            ImGuiWindowFlags windowFlags = 0;
            GLTexture m_cubeButtonTex,m_playButtonTex;
            ImGuizmo::OPERATION m_gizmoOperation = ImGuizmo::TRANSLATE;
            std::pair<float,float> lastViewportSize = {0.0f,0.0f};
            ImFont *smallFont = nullptr,*normalFont = nullptr,*bigFont = nullptr;
        };
    } // r8ge
} // video

#endif //R8GE_IMGUI_H
