//
// Created by karnatour on 5.2.24.
//

#include "Entity.h"
#include "Scene.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <random>
#include "../Video.h"
#include "../r8ge/src/core/PhysicsManager.h"

namespace r8ge {
    namespace video {
        unsigned long Entity::m_nextID = 0;

        Entity::Entity(Scene &scene) : m_id(m_nextID++), m_scene(scene) {
            Video::getRenderingService()->compileProgram(m_shader);
            m_transformation.model = glm::mat4(1.0f);
            m_transformation.projection = glm::perspective(glm::radians(45.0f),
                                                           Video::getGUIService()->getViewportWidth() /
                                                           Video::getGUIService()->getViewportHeight(),
                                                           0.1f, 1000.0f);
            m_transformation.model = glm::translate(m_transformation.model, glm::vec3(0.0f, 0.0f, 0.0f));
            m_transformation.model = glm::scale(m_transformation.model, glm::vec3(1.0f, 1.0f, 1.0f));
        }

        unsigned long Entity::getEntityID() const {
            return m_id;
        }


        void Entity::changeTransformation(const Transformation &transformation) {
            m_transformation = transformation;
        }

        bool Entity::getTextureState() const {
            return m_hasTexture;
        }

        bool Entity::getMaterialState() const {
            return m_hasMaterial;
        }

        void Entity::setUpdateFunction(Entity::UpdateFunction function) {
            m_updateFunction = function;
        }

        std::string Entity::getName() {
            return m_name;
        }

        Transformation &Entity::getTransformation() {
            return m_transformation;
        }

        bool Entity::getSelectionState() const {
            return m_isSelected;
        }

        void Entity::setSelectionState(bool state) {
            m_isSelected = state;
        }

        JPH::BodyCreationSettings Entity::getBodyCreationSettings() {
            return m_bodyCreationSettings;
        }

        std::string Entity::getTexturePath() {
            return m_texturePath;
        }

        bool &Entity::isTextureFlippedRef() {
            return m_flipTexture;
        }

        Material &Entity::getMaterial() {
            return m_material;
        }

        void EntityModel::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            m_model.render(m_shader, m_transformation);
        }

        EntityModel::EntityModel(Scene &scene, Model model) : Entity(scene), m_model(std::move(model)) {
            m_name = m_model.m_getNameVector()[0];
        }

        EntityCube::EntityCube(Scene &scene, Mesh cubeMesh) : Entity(scene), m_cubeMesh(std::move(cubeMesh)) {
            m_name = m_cubeMesh.getName();
            /*
            m_bodyCreationSettings = JPH::BodyCreationSettings(new JPH::BoxShape(JPH::Vec3(1.0f, 1.0f, 1.0f)),
                                                               JPH::RVec3(0, 0, 0),
                                                               JPH::Quat::sIdentity(), JPH::EMotionType::Dynamic,
                                                               ObjectLayers::MOVING);
                                                               */
        }

        void EntityCube::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            if (Video::m_editorMode) {
                m_transformation.projection = glm::perspective(glm::radians(45.0f),
                                                               Video::getGUIService()->getViewportWidth() /
                                                               Video::getGUIService()->getViewportHeight(),
                                                               0.1f, 1000.0f);
            } else {
                m_transformation.projection = glm::perspective(glm::radians(45.0f),
                                                               Video::getWindowingService()->getWindowWidth() /
                                                               Video::getWindowingService()->getWindowHeight(),
                                                               0.1f, 1000.0f);
            }
            m_cubeMesh.render(m_shader, m_transformation);
        }

        void EntityCube::changeTexture(const Texture2D &texture) {
            m_texture.setData(texture);
            m_texture.setType(texture.getType());
            m_cubeMesh.setTexture(std::vector<GLTexture>{m_texture});
            m_hasTexture = true;
        }


        void EntityCube::changeMaterial(const Material &material) {
            m_material = material;
            m_cubeMesh.setMaterial(material);
            m_hasMaterial = true;
        }

        void EntitySphere::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            m_sphereMesh.render(m_shader, m_transformation);
        }

        EntitySphere::EntitySphere(Scene &scene, Mesh sphereMesh) : Entity(scene), m_sphereMesh(std::move(sphereMesh)) {
            m_name = m_sphereMesh.getName();
        }

        void EntityCylinder::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            m_cylinderMesh.render(m_shader, m_transformation);
        }

        EntityCylinder::EntityCylinder(Scene &scene, Mesh cylinderMesh) : Entity(scene), m_cylinderMesh(std::move(cylinderMesh)) {
            m_name = m_cylinderMesh.getName();
        }

        EntityDirLight::EntityDirLight(Scene &scene, Mesh dirLightMesh) : Entity(scene), m_dirLightMesh(std::move(dirLightMesh)) {
            m_name = m_dirLightMesh.getName();
        }

        void EntityDirLight::render() {
            if (m_updateFunction != nullptr) {
                m_updateFunction();
            }
            m_transformation.view = m_scene.getCamera().getViewMatrix();
            if (Video::m_editorMode) {
                m_transformation.projection = glm::perspective(glm::radians(45.0f),
                                                               Video::getGUIService()->getViewportWidth() /
                                                               Video::getGUIService()->getViewportHeight(),
                                                               0.1f, 1000.0f);
            } else {
                m_transformation.projection = glm::perspective(glm::radians(45.0f),
                                                               Video::getWindowingService()->getWindowWidth() /
                                                               Video::getWindowingService()->getWindowHeight(),
                                                               0.1f, 1000.0f);
            }

            m_dirLightMesh.render(Scene::getShaderLibrary().getShader("LightEntity.glsl"), m_transformation);

        }

        void EntityDirLight::changeTexture(const Texture2D &texture) {
            m_texture.setData(texture);
            m_texture.setType(texture.getType());
            m_dirLightMesh.setTexture(std::vector<GLTexture>{m_texture});
            m_hasTexture = true;
        }

        void EntityDirLight::changeMaterial(const Material &material) {
            m_material = material;
            m_dirLightMesh.setMaterial(material);
            m_hasMaterial = true;
        }
    } // r8ge
} // video
