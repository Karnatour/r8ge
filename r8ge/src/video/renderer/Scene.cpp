//
// Created by karnatour on 4.2.24.
//

#include "Scene.h"
#include "../Video.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/string_cast.hpp>

namespace r8ge {
    namespace video {
        std::map<unsigned long, Entity *> Scene::m_entities;

        void Scene::addEntity(Entity *entity) {
            m_entities[entity->getEntityID()] = entity;
        }

        void Scene::removeEntity(unsigned long id) {
            auto it = m_entities.find(id);
            if (it != m_entities.end()) {
                delete it->second;
                m_entities.erase(it);
            }
        }


        void Scene::changeTexture(const Texture2D &texture) {
            if (m_selectedEntityPtr) {
                m_entities[m_selectedEntityPtr->getEntityID()]->changeTexture(texture);
            }
        }

        void Scene::changeMaterial(const Material &material) {
            if (m_selectedEntityPtr) {
                m_entities[m_selectedEntityPtr->getEntityID()]->changeMaterial(material);
            }
        }

        void Scene::changeTransformation(const Transformation &transform) {
            if (m_selectedEntityPtr) {
                m_entities[m_selectedEntityPtr->getEntityID()]->changeTransformation(transform);
            }
        }

        void Scene::handleTreeNodeSelect(unsigned long nodeIndex) {
            if (nodeIndex < m_entities.size()) {
                m_selectedEntityPtr = m_entities[nodeIndex];
            } else {
                m_selectedEntityPtr = nullptr;
            }
        }

        Entity *Scene::getEntity(unsigned long id) {
            auto it = m_entities.find(id);
            if (it != m_entities.end()) {
                if (it->second == nullptr) {
                    R8GE_LOG_WARNI("Found entity is nullptr");
                    return nullptr;
                }
                return it->second;
            } else {
                R8GE_LOG_WARNI("Returned entity is nullptr");
                return nullptr;
            }
        }

        void Scene::init() {
            if (!std::filesystem::exists("Engine/Shaders") || !std::filesystem::is_directory("Engine/Shaders")) {
                R8GE_LOG_ERROR("Engine shaders folder is missing");
            } else {
                for (const auto &file: std::filesystem::directory_iterator("Engine/Shaders")) {
                    m_shaderLibrary.addShader(file.path().string());
                }
            }
            m_shaderLibrary.compileAllShaders();
            m_skyBox = SkyBox(skyboxVertices, skyboxIndices, skyboxLocations, "skybox");

        }

        void Scene::copySelectedEntity() {
            if (m_selectedEntityPtr) {
                Entity *copiedEntity = m_selectedEntityPtr;
                addEntity(copiedEntity);
            }
        }

        void Scene::changeCamera(float deltaTime) {
            m_camera.changeCameraPosition(deltaTime);
        }

        void Scene::changeSkybox(const std::vector<std::string> &skyBoxLocations) {
            m_skyBox = SkyBox(skyboxVertices, skyboxIndices, skyboxLocations, "skybox");
        }

        void Scene::render(PhysicsManager &physicsManager) {
            auto it = m_entities.begin();
            while (it != m_entities.end()) {
                if (Video::m_editorMode == false) {
                    physicsManager.addBody(it->second);
                }
                if (std::abs(it->second->getTransformation().model[3].x) > 10000.0f ||
                    std::abs(it->second->getTransformation().model[3].y) > 10000.0f ||
                    std::abs(it->second->getTransformation().model[3].z) > 10000.0f) {
                    R8GE_LOG_ERROR("Entity {} got out of bounds", it->second->getName());
                    delete it->second;
                    it = m_entities.erase(it);
                    continue;
                    }
                it->second->render();
                ++it;
            }

            m_shaderLibrary.useShader("Skybox.glsl");
            Video::getRenderingService()->setUniformInt(m_shaderLibrary.getShader("Skybox.glsl"), "skybox", 0);
            m_skyboxTransformationRef.view = glm::mat4(glm::mat3(m_camera.getViewMatrix()));
            if (Video::m_editorMode) {
                m_skyboxTransformationRef.projection = glm::perspective(glm::radians(45.0f),
                                                                         Video::getGUIService()->getViewportWidth() /
                                                                         Video::getGUIService()->getViewportHeight(),
                                                                         0.1f, 100.0f);
            } else {
                m_skyboxTransformationRef.projection = glm::perspective(glm::radians(45.0f),
                                                                     Video::getWindowingService()->getWindowWidth() /
                                                                     Video::getWindowingService()->getWindowHeight(),
                                                                     0.1f, 100.0f);


            }
            m_skyBox.render(m_shaderLibrary.getShader("Skybox.glsl"));
        }


        Camera &Scene::getCamera() {
            return m_camera;
        }

        std::string Scene::getName() {
            return m_name;
        }

        std::map<unsigned long, Entity *> Scene::getEntitiesMap() {
            return m_entities;
        }

        Entity *Scene::getSelectedEntity() {
            if (m_selectedEntityPtr == nullptr) {
                return nullptr;
            } else {
                return m_selectedEntityPtr;
            }
        }

        void Scene::deselectAllEntities() {
            for (auto &entityPair: m_entities) {
                entityPair.second->setSelectionState(false);
            }
        }
    } // r8ge
} // video
