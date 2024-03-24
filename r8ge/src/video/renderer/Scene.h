#pragma once

#include "Entity.h"
#include "Camera.h"
#include "SkyBox.h"
#include <filesystem>
#include <map>
#include <utility>
#include "../r8ge/src/core/PhysicsManager.h"
#include "../renderingService/programManager/ShaderLibrary.h"

namespace r8ge {
    namespace video {

        class Scene {
        public:
            explicit Scene(std::string name) : m_name(std::move(name)) {};

            void init();

            void addEntity(Entity *entity);

            void removeEntity(unsigned long id);

            void copySelectedEntity();

            void render(PhysicsManager &physicsManager);

            void changeTexture(const Texture2D& texture);

            void changeMaterial(const Material& material);

            void changeTransformation(const Transformation& transform);

            void changeCamera(float deltaTime);

            void changeSkybox(const std::vector<std::string> &skyBoxLocations);

            void handleTreeNodeSelect(unsigned long nodeIndex);

            Camera& getCamera();

            static Entity* getEntity(unsigned long id);

            Entity* getSelectedEntity();

            void deselectAllEntities();

            std::string getName();

            std::map<unsigned long,Entity *> getEntitiesMap();

        private:
            Camera m_camera = Camera(glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
            static std::map<unsigned long, Entity *> m_entities;
            Entity *m_selectedEntityPtr = nullptr;
            ShaderLibrary m_shaderLibrary;
            std::string m_name;

            SkyBox m_skyBox;
            Transformation &m_skyboxTransformationRef = m_skyBox.getSkyBoxTransformationRef();
        };

    } // r8ge
} // video