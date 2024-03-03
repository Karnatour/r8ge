#ifndef R8GE_MESH_H
#define R8GE_MESH_H

#include "../renderingService/openGL/GLTexture.h"
#include "../types/Vertex.h"
#include "../renderingService/RenderingService.h"
#include "../types/SceneHelper.h"


namespace r8ge {
    namespace video {

        class Mesh {
        public:
            Mesh(const std::vector<VertexColorTexture3D> &vertices, const std::vector<unsigned int> &indices,
                 const std::vector<GLTexture> &textures,const std::string& name);

            void render(Program &shader, const Transformation &transformation);

            void setTexture(const std::vector<GLTexture> &textures);

            std::string getName();
        private:
            void setupRender();

            std::vector<VertexColorTexture3D> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<GLTexture> m_textures;
            std::shared_ptr<video::RenderingService> m_renderingService;
            std::string m_name;
        };

    } // r8ge
} // video

#endif //R8GE_MESH_H
