//
// Created by karnatour on 16.1.24.
//

#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "../../core/Input.h"


namespace r8ge {
    namespace video {
        glm::mat4 Camera::getViewMatrix() {
            return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        }

        //TODO: We need to check if we are not in GUI
        //TODO: Implement Mouse input from core
        void Camera::changeCameraPosition(float deltaTime, float xoffset, float yoffset) {
            if (r8ge::Input::isKeyPressed(r8ge::Key::W)) {
                m_Position += m_Front * m_MovementSpeed * deltaTime;
            }
            if (r8ge::Input::isKeyPressed(r8ge::Key::S)) {
                m_Position -= m_Front * m_MovementSpeed * deltaTime;
            }
            if (r8ge::Input::isKeyPressed(r8ge::Key::A)) {
                m_Position -= m_Right * m_MovementSpeed * deltaTime;
            }
            if (r8ge::Input::isKeyPressed(r8ge::Key::D)) {
                m_Position += m_Right * m_MovementSpeed * deltaTime;
            }

            xoffset *= m_MouseSensitivity;
            yoffset *= m_MouseSensitivity;

            m_Yaw += xoffset;
            m_Pitch += yoffset;

            if (m_Pitch > 89.0f)
                m_Pitch = 89.0f;
            if (m_Pitch < -89.0f)
                m_Pitch = -89.0f;

            updateCameraVectors();
            //R8GE_LOG("Delta time: {}, Camera position changed to X: {}, Y: {}, Z: {}", deltaTime, m_Position.x,
            //m_Position.y, m_Position.z);
        }

        void Camera::updateCameraVectors() {
            glm::vec3 front;
            front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
            front.y = sin(glm::radians(m_Pitch));
            front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

            m_Front = glm::normalize(front);
            m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
            m_Up = glm::normalize(glm::cross(m_Right, m_Front));
        }

    } // r8ge
} // video