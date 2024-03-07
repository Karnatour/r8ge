//
// Created by Vojta on 01.03.2024.
//

#include "SkyBox.h"

#include <GL/glew.h>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

namespace r8ge {
namespace video {
    SkyBox::SkyBox(const std::vector<Vertex3D> &vertices, const std::vector<unsigned int> &indices,
        const std::vector<std::string> &locations, const std::string &name) {
        m_vertices = vertices;
        m_indices = indices;
        m_name = name;
        m_skybox = GLSkyBox(locations);
        m_renderingService = video::RenderingService::create(video::RenderingService::API::OpenGL);

        setupRender();
    }

    void SkyBox::render(Program &shader) {
        glDepthFunc(GL_LEQUAL);
        m_renderingService->setProgram(shader);
        m_renderingService->setUniformInt(shader,"skybox",0);
        m_renderingService->setUniformMat4(shader, "projection", m_skyBoxTransformation.projection);
        m_renderingService->setUniformMat4(shader, "view", m_skyBoxTransformation.view);
        m_skybox.bindSkybox();
        m_renderingService->render(m_indices.size());
        glDepthFunc(GL_LESS);
    }

    std::string SkyBox::getName() {
        return m_name;
    }

    Transformation &SkyBox::getSkyBoxTransformationRef() {
        return m_skyBoxTransformation;
    }

    void SkyBox::setupRender() {
        const video::VertexBuffer vb(m_vertices, m_vertices[0].getLayout());
        const video::IndexBuffer ib(m_indices);

        m_renderingService->setVertexBuffer(vb);
        m_renderingService->setIndexBuffer(ib);
        m_renderingService->preRender();
    }
} // video
} // r8ge