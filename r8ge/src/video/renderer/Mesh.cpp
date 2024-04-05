//
// Created by karnatour on 25.1.24.
//

#include "Mesh.h"
#include <random>


namespace r8ge {
    namespace video {
        Mesh::Mesh(const std::vector<VertexColorTexture3D> &vertices, const std::vector<unsigned int> &indices,
                   const std::vector<GLTexture> &textures, const std::string &name) {
            m_vertices = vertices;
            m_indices = indices;
            m_textures = textures;
            m_name = name;
            m_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);
            setupRender();
        }

        void Mesh::render(Program &shader, const Transformation &transformation) {
            m_renderingService->setProgram(shader);
            m_renderingService->setUniformMat4(shader, "model", transformation.model);
            m_renderingService->setUniformMat4(shader, "view", transformation.view);
            m_renderingService->setUniformMat4(shader, "projection", transformation.projection);
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            unsigned int normalNr = 1;
            unsigned int heightNr = 1;
            if (!m_textures.empty()) {
                for (unsigned int i = 0; i < m_textures.size(); ++i) {
                    std::string type = m_textures[i].getType();
                    std::string number;
                    if (type == "texture_diffuse") {
                        number = std::to_string(diffuseNr++);
                    }
                    else if (type == "texture_specular") {
                        number = std::to_string(specularNr++);
                    }
                    else if (type == "texture_normal") {
                        number = std::to_string(normalNr++);
                    }
                    else if (type == "texture_height") {
                        number = std::to_string(heightNr++);
                    }
                    m_renderingService->setUniformInt(shader, type + number, static_cast<int>(i));
                    m_textures[i].bindTexture(i);
                }
            }
            m_renderingService->render(m_indices.size());
            if (!m_textures.empty()){
                GLTexture::unbindTexture();
            }
        }

        void Mesh::setTexture(const std::vector<GLTexture> &textures) {
            m_textures = textures;
        }

        void Mesh::setupRender() {
            const video::IndexBuffer ib(m_indices);
            const video::VertexBuffer vb(m_vertices, m_vertices[0].getLayout());

            m_renderingService->setVertexBuffer(vb);
            m_renderingService->setIndexBuffer(ib);
            m_renderingService->preRender();
        }

        std::string Mesh::getName() {
            return m_name;
        }
    } // r8ge
} // video