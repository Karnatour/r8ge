//
// Created by Vojta on 09.04.2024.
//

#pragma once

#include <glm/glm.hpp>

namespace r8ge {
    struct dirLight {
        glm::vec3 direction = glm::vec3(0.0f);
        glm::vec3 ambient = glm::vec3(0.0f);
        glm::vec3 diffuse = glm::vec3(0.0f);
        glm::vec3 specular = glm::vec3(0.0f);
    };

    struct pointLight {
        glm::vec3 position = glm::vec3(0.0f);
        glm::vec3 ambient = glm::vec3(0.0f);
        glm::vec3 diffuse = glm::vec3(0.0f);
        glm::vec3 specular = glm::vec3(0.0f);
        float constant = 0.0f;
        float linear = 0.0f;
        float quadratic = 0.0f;
    };
}
