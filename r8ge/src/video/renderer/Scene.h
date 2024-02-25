//
// Created by karnatour on 4.2.24.
//

#ifndef R8GE_SCENE_H
#define R8GE_SCENE_H

#include "Entity.h"
#include "Camera.h"
#include <filesystem>
#include <map>
#include <utility>

namespace r8ge {
    namespace video {

        class Scene {
        public:
            explicit Scene(std::string name) : m_name(std::move(name)) {};

            void init();

            void addEntity(Entity *entity);

            void removeEntity(unsigned long id);

            void copySelectedEntity();

            void render();

            void changeTexture(const Texture2D& texture);

            void changeMaterial(const Material& material);

            void changeTransformation(const Transformation& transform);

            void changeCamera(float deltaTime);

            void handleTreeNodeSelect(unsigned long nodeIndex);

            Camera& getCamera();

            Entity* getEntity(unsigned long id);

            Entity* getSelectedEntity();

            void deselectAllEntities();

            std::string getName();

            std::map<unsigned long,Entity *> getEntitiesMap();

        private:
            Camera m_camera = Camera(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f);
            std::map<unsigned long, Entity *> m_entities;
            Entity *m_selectedEntityPtr = nullptr;
            std::vector<Program> m_shaderLibrary;
            std::string m_name;
        };

    } // r8ge
} // video

#endif //R8GE_SCENESTRUCTS_H
