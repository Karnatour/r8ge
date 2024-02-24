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
            Mesh(std::vector<VertexColorTexture3D> &vertices, std::vector<unsigned int> &indices,
                 std::vector<GLTexture> &textures,const std::string& name);

            void render(Program &shader,Transformation &transformation);

            std::string getName();
        private:
            void setupRender();

            std::vector<VertexColorTexture3D> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<GLTexture> m_textures;
            std::shared_ptr<video::RenderingService> m_renderingService;
            std::string m_name;
            bool m_firstRenderLoop;
        };

    } // r8ge
} // video

#endif //R8GE_MESH_H
