//
// Created by karnatour on 5.2.24.
//

#ifndef R8GE_ENTITY_H
#define R8GE_ENTITY_H

#include "Model.h"
#include "Mesh.h"
#include <utility>

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

            void changeTexture(const Texture2D &texture);

            void changeMaterial(const Material &material);

            void changeTransformation(const Transformation &transformation);

            [[nodiscard]] bool getMaterialState() const;

            [[nodiscard]] bool getTextureState() const;

            [[nodiscard]] bool getSelectionState() const;

            void setSelectionState(bool state);

            std::string getName();

            Transformation &getTransformation();

            virtual ~Entity() = default;

        protected:
            static unsigned long m_nextID;
            unsigned long m_id;
            bool m_hasMaterial = false;
            bool m_hasTexture = false;
            bool m_isSelected = false;
            UpdateFunction m_updateFunction{};
            Program m_shader = Program("Engine/Shaders/EntityDefault.glsl");
            GLTexture m_texture;
            Material m_material{};
            Transformation m_transformation;
            Scene &m_scene;
            std::string m_name;

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

    } // r8ge
} // video

#endif //R8GE_ENTITY_H
