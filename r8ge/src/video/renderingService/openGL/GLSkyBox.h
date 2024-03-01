//
// Created by vojta on 29.02.2024.
//

#ifndef R8GE_GLSKYBOX_H
#define R8GE_GLSKYBOX_H

namespace r8ge
{
    namespace video
    {

        class GLSkyBox
        {
        public:
            GLSkyBox();
            explicit GLSkyBox(const std::vector<std::string>& paths);
            unsigned int getSkybox();
            void bindSkybox(unsigned int unit);
        private:
            unsigned int m_skybox;
        };

    } // r8ge
} // video

#endif //R8GE_GLSKYBOX_H
