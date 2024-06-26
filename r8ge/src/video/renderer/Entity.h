//
// Created by karnatour on 5.2.24.
//

#pragma once

#include "Model.h"
#include "Mesh.h"
#include <utility>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>

namespace r8ge {
    namespace video {

        class Scene;

        class Entity {
        public:
            typedef void (*UpdateFunction)();

            explicit Entity(Scene &scene);

            [[nodiscard]] unsigned long getEntityID() const;

            virtual void render() = 0;

            void setUpdateFunction(UpdateFunction function);

            //[[nodiscard]] virtual Entity *clone() const = 0;

            virtual void changeTexture(const Texture2D &texture) = 0;

            virtual void changeMaterial(const Material &material) = 0;

            void changeTransformation(const Transformation &transformation);

            [[nodiscard]] bool getMaterialState() const;

            [[nodiscard]] bool getTextureState() const;

            bool& isTextureFlippedRef();

            [[nodiscard]] bool getSelectionState() const;

            void setSelectionState(bool state);

            JPH::BodyCreationSettings getBodyCreationSettings();

            std::string getName();

            std::string getTexturePath();

            Transformation &getTransformation();

            Material &getMaterial();

            virtual ~Entity() = default;

        protected:
            static unsigned long m_nextID;
            unsigned long m_id;
            bool m_hasMaterial = false;
            bool m_hasTexture = false;
            bool m_flipTexture = false;
            bool m_isSelected = false;
            UpdateFunction m_updateFunction{};
            Program m_shader = Program("Engine/Shaders/EntityDefault.glsl");
            GLTexture m_texture;
            Material m_material;
            Transformation m_transformation;
            Scene &m_scene;
            std::string m_name,m_texturePath;
            JPH::BodyCreationSettings m_bodyCreationSettings;
        };

        class EntityModel : public Entity {
        public:
            explicit EntityModel(Scene &scene, Model model);

            void render() override;

        private:
            Model m_model;
        };


        class EntityCube : public Entity {
        public:
            explicit EntityCube(Scene &scene, Mesh cubeMesh);

            void changeTexture(const Texture2D &texture) override;

            void changeMaterial(const Material &material) override;

            void render() override;

        private:
            Mesh m_cubeMesh;
        };

        class EntitySphere : public Entity {
        public:
            explicit EntitySphere(Scene &scene, Mesh sphereMesh);

            void render() override;

        private:
            Mesh m_sphereMesh;
        };

        class EntityCylinder : public Entity {
        public:
            explicit EntityCylinder(Scene &scene, Mesh cylinderMesh);

            void render() override;

        private:
            Mesh m_cylinderMesh;
        };

        class EntityDirLight : public Entity {
        public:
            explicit EntityDirLight(Scene &scene, Mesh dirLightMesh);

            void changeTexture(const Texture2D &texture) override;

            void changeMaterial(const Material &material) override;

            void render() override;
        private:
            Mesh m_dirLightMesh;

        };

    } // r8ge
} // video

