//
// Created by karnatour on 8.2.24.
//

#ifndef R8GE_SCENEHELPER_H
#define R8GE_SCENEHELPER_H


namespace r8ge {
    struct Transformation {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };

    struct Material {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        float shine;
    };

    inline std::vector<unsigned int> cubeIndices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3
    };

// Define the vertices for a cube with red color
    inline std::vector<VertexColorTexture3D> cubeVertices = {
            {-1.0f, -1.0f, 1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f,
                                            1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  -1.0f, 1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f,
                                            1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f,
                                            1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f,  1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f,
                                            1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},

            {-1.0f, -1.0f, -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f,
                                            1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  -1.0f, -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f,
                                            1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f,
                                            1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f,  -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f,
                                            1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f}
    };

}
#endif //R8GE_SCENEHELPER_H
