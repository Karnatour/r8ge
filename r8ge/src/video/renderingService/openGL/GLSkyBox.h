//
// Created by vojta on 29.02.2024.
//

#pragma once

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
            void bindSkybox();
        private:
            unsigned int m_skybox;
        };

    } // r8ge
} // video

