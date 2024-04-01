#include "Video.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <r8ge/r8ge.h>

#include "imgui.h"
#include "../core/PhysicsManager.h"
#include "renderingService/openGL/GLFrameBuffer.h"
#include "renderer/Scene.h"
#include "renderer/SkyBox.h"

namespace r8ge {
    std::shared_ptr<video::WindowingService> Video::s_windowingService = nullptr;
    std::shared_ptr<video::RenderingService> Video::s_renderingService = nullptr;
    std::shared_ptr<video::GUIService> Video::s_guiService = nullptr;
    bool r8ge::Video::m_editorMode = true, Video::m_firstFrameLoop = true;
    std::shared_ptr<TimeStep> Video::s_timestep = nullptr;
    video::GLFrameBuffer frameBuffer;
    video::Scene scene("Main scene");

    PhysicsManager physicsManager;

    Video::Video() : m_title("R8GE-video Engine") {
        s_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);
        s_windowingService = video::WindowingService::create();
        s_guiService = video::GUIService::create();
        s_timestep = std::make_shared<TimeStep>();

        s_windowingService->setKeyPressedCallback(Input::getKeyActionCallback());
        s_windowingService->setMousePressedCallback(Input::getMouseActionCallback());
        s_windowingService->setMousePosCallback(Input::getMouseMovedCallback());
        s_windowingService->setScrollCallback(Input::getScrollCallback());
    }

    Video::~Video() {
        s_windowingService = nullptr;
        s_renderingService = nullptr;
    }

    void Video::init() {
        physicsManager.init();
        s_windowingService->init();
        s_windowingService->createMainWindow(800, 600, m_title);
        s_windowingService->setEventCallbacks();
        s_windowingService->setContextOfMainWindow();
        s_windowingService->setGLContext();
        s_windowingService->setVsync(true);
        s_renderingService->init();
        s_guiService->init(*s_windowingService);
        scene.init();
        R8GE_LOG("R8GE-Video initialized");
    }

    void Video::run() {
        glEnable(GL_DEPTH_TEST);
        R8GE_LOG("Video starting to run main loop");
        s_windowingService->setFrameBuffer(frameBuffer);
        video::Texture2D tex("Engine/Textures/tex.jpg", true);
        s_guiService->beginFrame();
        s_guiService->renderEditorUI(frameBuffer, scene);
        s_guiService->endFrame(*s_windowingService);
        frameBuffer.setBuffer(s_guiService->getViewportWidth(), s_guiService->getViewportHeight());
        while (Ar8ge::isRunning()) {
            double time = glfwGetTime();
            s_timestep->setTime(time - m_lastFrameRenderTime);
            m_lastFrameRenderTime = time;


            s_guiService->beginFrame();
            if (m_editorMode) {
                frameBuffer.bind();
            }

            scene.changeCamera(s_timestep->getSeconds());
            s_renderingService->setClearColor(ColorRGBA(0, 0, 30, 255));
            s_renderingService->clear();
            scene.render(physicsManager);
            physicsManager.update();

            if (m_editorMode) {
                s_guiService->insertSceneIntoSceneItems(scene);
                frameBuffer.unbind();
                s_guiService->renderEditorUI(frameBuffer, scene);
            }

            s_guiService->endFrame(*s_windowingService);


            s_windowingService->swapBuffersOfMainWindow();
            s_windowingService->poolEvents();
            m_firstFrameLoop = false;
        }
    }

    void Video::exit() {
        s_windowingService->destroyMainWindow();

        s_windowingService->exit();
        s_renderingService->exit();
        s_guiService->exit();

        R8GE_LOG_INFOR("R8GE-Video released");
    }

    std::shared_ptr<video::WindowingService> Video::getWindowingService() {
        return s_windowingService;
    }

    std::shared_ptr<video::RenderingService> Video::getRenderingService() {
        return s_renderingService;
    }

    std::shared_ptr<video::GUIService> Video::getGUIService() {
        return s_guiService;
    }

    std::shared_ptr<TimeStep> Video::getTimeStep() {
        return s_timestep;
    }
}
