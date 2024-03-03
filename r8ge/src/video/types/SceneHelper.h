//
// Created by karnatour on 8.2.24.
//

#pragma once

namespace r8ge {
    struct Transformation {
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(0.0f);
        glm::mat4 projection = glm::mat4(0.0f);
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

    inline std::vector<unsigned int> skyboxIndices = {
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };

    inline std::vector<Vertex3D> skyboxVertices = {
        {-1.0, -1.0, 1.0},
        {1.0, -1.0, 1.0},
        {1.0, -1.0, -1.0},
        {-1.0, -1.0, -1.0},
        {-1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 1.0, -1.0},
        {-1.0, 1.0, -1.0},
    };

    inline std::vector<std::string> skyboxLocations = {
        "Engine/Skybox/right.png",
        "Engine/Skybox/left.png",
        "Engine/Skybox/top.png",
        "Engine/Skybox/bottom.png",
        "Engine/Skybox/front.png",
        "Engine/Skybox/back.png"

    };
}
