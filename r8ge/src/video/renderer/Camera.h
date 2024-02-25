//
// Created by karnatour on 16.1.24.
//

#ifndef R8GE_CAMERA_H
#define R8GE_CAMERA_H

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

            void changeCameraPosition(float deltaTime,float xoffset, float yoffset);

        private:
            void updateCameraVectors();
            glm::vec3 m_Position, m_WorldUp;
            glm::vec3 m_Front, m_Up, m_Right;
            float m_Yaw = -90.0f, m_Pitch = 0.0f, m_MovementSpeed = 2.5f, m_MouseSensitivity = 0.1f, m_Zoom = 45.0f;
        };

    } // r8ge
} // video

#endif //R8GE_CAMERA_H
