//
// Created by karnatour on 8.2.24.
//

#pragma once

#include <glm/glm.hpp>
#include "Color.h"
#include <vector>
#include "Vertex.h"

namespace r8ge {
    struct Transformation {
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(0.0f);
        glm::mat4 projection = glm::mat4(0.0f);
    };

    inline std::vector<unsigned int> cubeIndices = {
            // front
            0, 1, 2,
            2, 3, 0,
            // top
            4, 5, 6,
            6, 7, 4,
            // back
            8, 9, 10,
            10, 11, 8,
            // bottom
            12, 13, 14,
            14, 15, 12,
            // left
            16, 17, 18,
            18, 19, 16,
            // right
            20, 21, 22,
            22, 23, 20,
    };

    inline std::vector<VertexColorTexture3D> cubeVertices = {
            // front
            {-1.0f, -1.0f, 1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  -1.0f, 1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f,  1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},

            // top
            {-1.0f, 1.0f,  1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f,  -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},

            // back
            {1.0f,  -1.0f, -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, -1.0f, -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f,  -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},

            // bottom
            {-1.0f, -1.0f, -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  -1.0f, -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  -1.0f, 1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, -1.0f, 1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},

            // left
            {-1.0f, -1.0f, -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, -1.0f, 1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f,  1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {-1.0f, 1.0f,  -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},

            // right
            {1.0f,  -1.0f, 1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  -1.0f, -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  -1.0f, ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},
            {1.0f,  1.0f,  1.0f,  ColorRGBA(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f},

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
            {1.0,  -1.0, 1.0},
            {1.0,  -1.0, -1.0},
            {-1.0, -1.0, -1.0},
            {-1.0, 1.0,  1.0},
            {1.0,  1.0,  1.0},
            {1.0,  1.0,  -1.0},
            {-1.0, 1.0,  -1.0},
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
