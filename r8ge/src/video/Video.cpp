#include "Video.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <r8ge/r8ge.h>

#include "renderingService/openGL/GLFrameBuffer.h"
#include "renderer/Scene.h"
#include "renderer/SkyBox.h"

namespace r8ge {
    std::shared_ptr<video::WindowingService> Video::s_windowingService = nullptr;
    std::shared_ptr<video::RenderingService> Video::s_renderingService = nullptr;
    std::shared_ptr<video::GUIService> Video::s_guiService = nullptr;
    std::shared_ptr<TimeStep> Video::s_timestep = nullptr;
    video::GLFrameBuffer frameBuffer;
    video::Scene scene("Main scene");

    Video::Video() : m_title("R8GE-video Engine") {
        s_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);
        s_windowingService = video::WindowingService::create();
        s_guiService = video::GUIService::create();
        s_timestep = std::make_shared<TimeStep>();

        s_windowingService->setKeyPressedCallback(Input::getKeyActionCallback());
        s_windowingService->setMousePressedCallback(Input::getMouseActionCallback());
        s_windowingService->setMouseOffsetCallback(Input::getMouseOffsetCallback());
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
        video::Program test_program("Engine/Shaders/model.glsl");
        video::Program skyboxshader("Engine/Shaders/Skybox.glsl");
        s_renderingService->compileProgram(test_program);
        s_renderingService->compileProgram(skyboxshader);
        video::Texture2D tex("Engine/Textures/tex.jpg",true);
        //video::Model model("Engine/Models/backpack/backpack.obj");
        video::SkyBox skybox(skyboxVertices,skyboxIndices,skyboxLocations,"skybox");
        Transformation &temp = skybox.getSkyBoxTransformationRef();
        frameBuffer.setBuffer(s_windowingService->getWidth(), s_windowingService->getHeight());
        while (Ar8ge::isRunning()) {
            double time = glfwGetTime();
            s_timestep->setTime(time - m_lastFrameRenderTime);
            m_lastFrameRenderTime = time;
            float deltatime = time - m_lastFrameRenderTime;
            scene.changeCamera(static_cast<float>(s_timestep->getSeconds()));

            s_guiService->beginFrame();

            frameBuffer.bind();

            s_renderingService->setClearColor(ColorRGBA(0, 0, 30, 255));
            s_renderingService->clear();

            //if (scene.getSelectedEntity()!=nullptr) {
            //    scene.getSelectedEntity()->changeTexture(tex);
            //}
            s_renderingService->setProgram(test_program);
            scene.render();

            s_renderingService->setProgram(skyboxshader);
            s_renderingService->setUniformInt(skyboxshader,"skybox",0);
            temp.view = glm::mat4(glm::mat3(scene.getCamera().getViewMatrix()));
            temp.projection = glm::perspective(glm::radians(45.0f),
                                              static_cast<float>(s_windowingService->getWidth()) /
                                              static_cast<float>(s_windowingService->getHeight()),
                                              0.1f, 100.0f);
            skybox.render(skyboxshader);

            s_guiService->insertSceneIntoSceneItems(scene);

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

    std::shared_ptr<TimeStep> Video::getTimeStep(){
        return s_timestep;
    }
}
