#pragma once

#include <glm/glm.hpp>

namespace r8ge
{
    namespace video
    {

        class Camera
        {
        public:
            Camera(glm::vec3 position, glm::vec3 worldUp) : m_Position(position),
                                                            m_WorldUp(worldUp)
            {
                m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
                m_Yaw = -90.0f;
                m_Pitch = 0.0f;
                m_MouseSensitivity = 0.05f;
                m_MovementSpeed = 2.5f;
                updateCameraVectors();
            };

            glm::mat4 getViewMatrix();

            void changeCameraPosition(float deltaTime);

        private:
            void updateCameraVectors();

            glm::vec3 m_Position, m_WorldUp;
            glm::vec3 m_Front, m_Up, m_Right;
            float m_Yaw, m_Pitch, m_MovementSpeed, m_MouseSensitivity, m_Zoom = 45.0f;
            bool m_bInputModeOn = false;
            double m_lastX = 0,m_lastY = 0; //before click
            double m_lastMoveX = 0,m_lastMoveY = 0;
        };

    } // r8ge
} // video