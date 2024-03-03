//
// Created by karnatour on 4.2.24.
//

#include "Scene.h"
#include "../Video.h"
#include <glm/ext/matrix_clip_space.hpp>

namespace r8ge {
    namespace video {
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
            if (nodeIndex > 0 && nodeIndex < m_entities.size()) {
                m_selectedEntityPtr = m_entities[nodeIndex];
            }
            else {
                m_selectedEntityPtr = nullptr;
            }
        }

        std::vector<Program> Scene::getShaderLibrary() {
            return m_shaderLibrary;
        }

        Entity* Scene::getEntity(unsigned long id) {
            auto it = m_entities.find(id);
            if (it != m_entities.end()) {
                return it->second;
            }
            else {
                R8GE_LOG_WARNI("Returned entity is nullptr");
                return nullptr;
            }

        }

        void Scene::init() {

            if (!std::filesystem::exists("Engine/Shaders") || !std::filesystem::is_directory("Engine/Shaders")) {
                R8GE_LOG_ERROR("Engine shaders folder is missing");
            }
            else {
                for (const auto &file : std::filesystem::directory_iterator("Engine/Shaders")) {
                    m_shaderLibrary.emplace_back(file.path().string());
                }
            }

            m_skyBox = SkyBox(skyboxVertices,skyboxIndices,skyboxLocations,"skybox");
            m_skyboxTransformation = &m_skyBox.getSkyBoxTransformationRef();
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
            m_skyBox = SkyBox(skyboxVertices,skyboxIndices,skyboxLocations, "skybox");
        }

        void Scene::render() {
            for (const auto &pair: m_entities) {
                pair.second->render();
            }
            m_skyboxTransformation->view = m_camera.getViewMatrix();
            m_skyboxTransformation->projection = glm::perspective(glm::radians(95.0f),
                                                                 static_cast<float>(Video::getWindowingService()->
                                                                     getWidth()) /
                                                                 static_cast<float>(Video::getWindowingService()->
                                                                     getHeight()),
                                                                 0.1f, 100.0f);

            //m_skyBox.render(m_shaderLibrary[2]);
        }

        Camera& Scene::getCamera() {
            return m_camera;
        }

        std::string Scene::getName() {
            return m_name;
        }

        std::map<unsigned long, Entity *> Scene::getEntitiesMap() {
            return m_entities;
        }

        Entity *Scene::getSelectedEntity() {
            if (m_selectedEntityPtr==nullptr) {
                return nullptr;
            }
            else {
                return m_selectedEntityPtr;
            }
        }

        void Scene::deselectAllEntities() {
            for (auto &entityPair : m_entities) {
                entityPair.second->setSelectionState(false);
            }
        }

    } // r8ge
} // video