//
// Created by Vojta on 01.03.2024.
//

#pragma once

#include "../types/Vertex.h"
#include "../renderingService/RenderingService.h"
#include "../renderingService/openGL/GLSkyBox.h"
#include "../types/SceneHelper.h"

namespace r8ge {
    namespace video {
        class SkyBox {
        public:

            SkyBox() = default;

            SkyBox(const std::vector<Vertex3D> &vertices, const std::vector<unsigned int> &indices,
                   const std::vector<std::string> &locations, const std::string &name);

            void render(Program &shader);

            std::string getName();

            Transformation& getSkyBoxTransformationRef();

        private:
            void setupRender();

            std::vector<Vertex3D> m_vertices;
            std::vector<unsigned int> m_indices;
            GLSkyBox m_skybox;
            std::shared_ptr<RenderingService> m_renderingService;
            std::string m_name;
            Transformation m_skyBoxTransformation;
        };
    } // video
} // r8ge

