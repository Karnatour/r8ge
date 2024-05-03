//
// Created by Vojta on 08.04.2024.
//

#pragma once

#include <glm/glm.hpp>

namespace r8ge{

    struct Material {
        glm::vec3 ambient = glm::vec3(0.0f);
        glm::vec3 diffuse = glm::vec3(0.0f);
        glm::vec3 specular = glm::vec3(0.0f);
        float shine = 0.0f;
        std::string name;
    };

    Material brass = {
            {0.329412f, 0.223529f, 0.027451f},
            {0.780392f, 0.568627f, 0.113725f},
            {0.992157f, 0.941176f, 0.807843f},
            27.8974f,"Brass"
    };

    Material bronze = {
            {0.2125f, 0.1275f, 0.054f},
            {0.714f, 0.4284f, 0.18144f},
            {0.393548f, 0.271906f, 0.166721f},
            25.6f,"Bronze"
    };

    Material polishedBronze = {
            {0.25f, 0.148f, 0.06475f},
            {0.4f, 0.2368f, 0.1036f},
            {0.774597f, 0.458561f, 0.200621f},
            76.8f,"Polished Bronze"
    };

    Material chrome = {
            {0.25f, 0.25f, 0.25f},
            {0.4f, 0.4f, 0.4f},
            {0.774597f, 0.774597f, 0.774597f},
            76.8f,"Chrome"
    };

    Material copper = {
            {0.19125f, 0.0735f, 0.0225f},
            {0.7038f, 0.27048f, 0.0828f},
            {0.256777f, 0.137622f, 0.086014f},
            12.8f,"Copper"
    };

    Material polishedCopper = {
            {0.2295f, 0.08825f, 0.0275f},
            {0.5508f, 0.2118f, 0.066f},
            {0.580594f, 0.223257f, 0.0695701f},
            51.2f,"Polished Copper"
    };

    Material gold = {
            {0.24725f, 0.1995f, 0.0745f},
            {0.75164f, 0.60648f, 0.22648f},
            {0.628281f, 0.555802f, 0.366065f},
            51.2f,"Gold"
    };

    Material polishedGold = {
            {0.24725f, 0.2245f, 0.0645f},
            {0.34615f, 0.3143f, 0.0903f},
            {0.797357f, 0.723991f, 0.208006f},
            83.2f,"Polished Gold"
    };

    Material tin = {
            {0.105882f, 0.058824f, 0.113725f},
            {0.427451f, 0.470588f, 0.541176f},
            {0.333333f, 0.333333f, 0.521569f},
            9.84615f,"Tin"
    };

    Material silver = {
            {0.19225f, 0.19225f, 0.19225f},
            {0.50754f, 0.50754f, 0.50754f},
            {0.508273f, 0.508273f, 0.508273f},
            51.2f,"Silver"
    };

    Material polishedSilver = {
            {0.23125f, 0.23125f, 0.23125f},
            {0.2775f, 0.2775f, 0.2775f},
            {0.773911f, 0.773911f, 0.773911f},
            89.6f,"Polished Silver"
    };

    Material emerald = {
            {0.0215f, 0.1745f, 0.0215f},
            {0.07568f, 0.61424f, 0.07568f},
            {0.633f, 0.727811f, 0.633f},
            76.8f,"Emerald"
    };

    Material jade = {
            {0.135f, 0.2225f, 0.1575f},
            {0.54f, 0.89f, 0.63f},
            {0.316228f, 0.316228f, 0.316228f},
            12.8f,"Jade"
    };

    Material obsidian = {
            {0.05375f, 0.05f, 0.06625f},
            {0.18275f, 0.17f, 0.22525f},
            {0.332741f, 0.328634f, 0.346435f},
            38.4f,"Obsidian"
    };

    Material pearl = {
            {0.25f, 0.20725f, 0.20725f},
            {1.0f, 0.829f, 0.829f},
            {0.296648f, 0.296648f, 0.296648f},
            11.264f,"Pearl"
    };

    Material ruby = {
            {0.1745f, 0.01175f, 0.01175f},
            {0.61424f, 0.04136f, 0.04136f},
            {0.727811f, 0.626959f, 0.626959f},
            76.8f,"Ruby"
    };

    Material turquoise = {
            {0.1f, 0.18725f, 0.1745f},
            {0.396f, 0.74151f, 0.69102f},
            {0.297254f, 0.30829f, 0.306678f},
            12.8f,"Turquoise"
    };

    Material blackPlastic = {
            {0.0f, 0.0f, 0.0f},
            {0.01f, 0.01f, 0.01f},
            {0.50f, 0.50f, 0.50f},
            32.0f,"Black Plastic"
    };

    Material cyanPlastic = {
            {0.0f, 0.1f, 0.06f},
            {0.0f, 0.50980392f, 0.50980392f},
            {0.50196078f, 0.50196078f, 0.50196078f},
            32.0f,"Cyan Plastic"
    };

    Material greenPlastic = {
            {0.0f, 0.0f, 0.0f},
            {0.1f, 0.35f, 0.1f},
            {0.45f, 0.55f, 0.45f},
            32.0f,"Green Plastic"
    };

    Material redPlastic = {
            {0.0f, 0.0f, 0.0f},
            {0.5f, 0.0f, 0.0f},
            {0.7f, 0.6f, 0.6f},
            32.0f,"Red Plastic"
    };

    Material whitePlastic = {
            {0.0f, 0.0f, 0.0f},
            {0.55f, 0.55f, 0.55f},
            {0.70f, 0.70f, 0.70f},
            32.0f,"White Plastic"
    };

    Material yellowPlastic = {
            {0.0f, 0.0f, 0.0f},
            {0.5f, 0.5f, 0.0f},
            {0.60f, 0.60f, 0.50f},
            32.0f,"Yellow Plastic"
    };

    Material blackRubber = {
            {0.02f, 0.02f, 0.02f},
            {0.01f, 0.01f, 0.01f},
            {0.4f, 0.4f, 0.4f},
            10.0f,"Black Rubber"
    };

    Material cyanRubber = {
            {0.0f, 0.05f, 0.05f},
            {0.4f, 0.5f, 0.5f},
            {0.04f, 0.7f, 0.7f},
            10.0f,"Cyan Rubber"
    };

    Material greenRubber = {
            {0.0f, 0.05f, 0.0f},
            {0.4f, 0.5f, 0.4f},
            {0.04f, 0.7f, 0.04f},
            10.0f,"Green Rubber"
    };

    Material redRubber = {
            {0.05f, 0.0f, 0.0f},
            {0.5f, 0.4f, 0.4f},
            {0.7f, 0.04f, 0.04f},
            10.0f,"Red Rubber"
    };

    Material whiteRubber = {
            {0.05f, 0.05f, 0.05f},
            {0.5f, 0.5f, 0.5f},
            {0.7f, 0.7f, 0.7f},
            10.0f,"White Rubber"
    };

    Material yellowRubber = {
            {0.05f, 0.05f, 0.0f},
            {0.5f, 0.5f, 0.4f},
            {0.7f, 0.7f, 0.04f},
            10.0f,"Yellow Rubber"
    };

    std::vector<Material> materials = {
            brass,
            bronze,
            polishedBronze,
            chrome,
            copper,
            polishedCopper,
            gold,
            polishedGold,
            tin,
            silver,
            polishedSilver,
            emerald,
            jade,
            obsidian,
            pearl,
            ruby,
            turquoise,
            blackPlastic,
            cyanPlastic,
            greenPlastic,
            redPlastic,
            whitePlastic,
            yellowPlastic,
            blackRubber,
            cyanRubber,
            greenRubber,
            redRubber,
            whiteRubber,
            yellowRubber
    };

}
