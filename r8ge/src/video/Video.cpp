#include "Video.h"

#include <r8ge/r8ge.h>

#include "renderer/Camera.h"
#include "renderingService/openGL/GLFrameBuffer.h"
#include "renderer/Scene.h"
#include "GLFW/glfw3.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace r8ge {
    video::Camera cam(0.0f, 0.0f, 3.0f, 0.0f, 1.0f, -1.0f);
    std::shared_ptr<video::WindowingService> Video::s_windowingService = nullptr;
    std::shared_ptr<video::RenderingService> Video::s_renderingService = nullptr;
    std::shared_ptr<video::GUIService> Video::s_guiService = nullptr;
    video::GLFrameBuffer frameBuffer;
    video::Scene scene("Main scene");


    Video::Video() : m_title("R8GE-video Engine") {
        // TODO: Config file, rendering API
        s_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);

        s_windowingService = video::WindowingService::create();
        s_guiService = video::GUIService::create();

        s_windowingService->setKeyPressedCallback(Input::getKeyActionCallback());
        s_windowingService->setMousePressedCallback(Input::getMouseActionCallback());
    }

    Video::~Video() {
        s_windowingService = nullptr;
        s_renderingService = nullptr;
    }

    void Video::init() {
        s_windowingService->init();
        s_windowingService->createMainWindow(800, 600, m_title);
        s_windowingService->setEventCallbacks();
        s_windowingService->setContextOfMainWindow();
        s_windowingService->setGLContext();
        s_windowingService->setVsync(true);

        s_renderingService->init();
        s_guiService->init(*s_windowingService);
        R8GE_LOG("R8GE-Video initialized");
    }

    void Video::run() {
        glEnable(GL_DEPTH_TEST);
        R8GE_LOG("Video starting to run main loop");
        scene.init();
        s_windowingService->setFrameBuffer(frameBuffer);
        frameBuffer.setBuffer(s_windowingService->getWidth(), s_windowingService->getHeight());
        while (Ar8ge::isRunning()) {
            //TODO: Replace this second timestep
            double time = glfwGetTime();
            TimeStep timestep(time - m_lastFrameRenderTime);
            m_lastFrameRenderTime = time;

            scene.changeCamera(static_cast<float>(timestep.getSeconds()));

            s_guiService->beginFrame();

            frameBuffer.bind();

            s_renderingService->setClearColor(ColorRGBA{0, 0, 30, 1.0});
            s_renderingService->clear();

            scene.render();

            s_guiService->insertSceneIntoSceneItems(scene);
            s_guiService->showDemoWindow();

            frameBuffer.unbind();

            s_guiService->render(frameBuffer,scene);
            s_guiService->endFrame(*s_windowingService);

            s_windowingService->swapBuffersOfMainWindow();
            s_windowingService->poolEvents();
        }

    }

    void Video::exit() {

        s_windowingService->destroyMainWindow();

        s_windowingService->exit();
        s_renderingService->exit();

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

}