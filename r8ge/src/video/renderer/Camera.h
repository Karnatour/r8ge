#pragma once

#include <glm/glm.hpp>

namespace r8ge
{
    namespace video
    {

        class Camera
        {
        public:
            Camera(glm::vec3 position, glm::vec3 worldUp);

            glm::mat4 getViewMatrix();

            void changeCameraPosition(float deltaTime);

        private:
            void updateCameraVectors();

            glm::vec3 m_Position, m_WorldUp;
            glm::vec3 m_Front, m_Up, m_Right;
            float m_Yaw, m_Pitch, m_MovementSpeed, m_MouseSensitivity, m_Zoom = 45.0f;
            bool m_bInputModeOn = false;
            double m_lastX = 0,m_lastY = 0;
            float m_minMovementSpeed = 5.0f, m_maxMovementSpeed = 150.0f;
        };

    } // r8ge
} // video