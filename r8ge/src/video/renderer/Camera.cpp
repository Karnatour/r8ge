//
// Created by karnatour on 16.1.24.
//

#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "../../core/Input.h"
#include "../../core/events/MouseEvents.h"
#include "../../video/Video.h"

namespace r8ge {
    namespace video {
        glm::mat4 Camera::getViewMatrix() {
            return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        }

        //TODO: We need to check if we are not in GUI
        void Camera::changeCameraPosition(float deltaTime) {
            if (r8ge::Input::isKeyPressed(r8ge::Key::MBUTTON_RIGHT) || m_firstMouse) {
                glfwSetInputMode(Video::getWindowingService()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

                float velocity = m_MovementSpeed * deltaTime;

                if (r8ge::Input::isKeyPressed(r8ge::Key::W))
                    m_Position += m_Front * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::S))
                    m_Position -= m_Front * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::A))
                    m_Position -= m_Right * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::D))
                    m_Position += m_Right * velocity;

                if (r8ge::Input::isMouseMoved()) {
                    std::pair<double, double> offset = r8ge::Input::getMouseOffset();
                    double xoffset = offset.first;
                    double yoffset = offset.second;

                    xoffset *= m_MouseSensitivity;
                    yoffset *= m_MouseSensitivity;

                    m_Yaw += xoffset;
                    m_Pitch += yoffset;

                    if (m_Pitch > 89.0f)
                        m_Pitch = 89.0f;
                    if (m_Pitch < -89.0f)
                        m_Pitch = -89.0f;

                    m_firstMouse = false;
                }

                // Update camera vectors
                updateCameraVectors();
            } else {
                glfwSetInputMode(Video::getWindowingService()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
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
