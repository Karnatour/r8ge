#pragma once

#include <glm/glm.hpp>

namespace r8ge {
    namespace video {

        class Camera {
        public:
            Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch) : m_Position(position),
                                                                                    m_WorldUp(worldUp),
                                                                                    m_Yaw(yaw), m_Pitch(pitch) {

            };

            Camera(float positionX, float positionY, float positionZ, float worldUpX, float worldUpY, float worldUpZ)
                    : m_Position(
                    positionX, positionY, positionZ), m_WorldUp(worldUpX, worldUpY, worldUpZ) {
            };

            glm::mat4 getViewMatrix();

            void changeCameraPosition(float deltaTime);

        private:
            void updateCameraVectors();
            glm::vec3 m_Position, m_WorldUp;
            glm::vec3 m_Front, m_Up, m_Right;
            float m_Yaw = -90.0f, m_Pitch = 0.0f, m_MovementSpeed = 2.5f, m_MouseSensitivity = 0.1f, m_Zoom = 45.0f;
            bool m_firstMouse = true;
            float m_lastX= 0;
            float m_lastY= 0;
        };

    } // r8ge
} // video