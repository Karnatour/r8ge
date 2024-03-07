#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "../../core/Input.h"
#include "../Video.h"

namespace r8ge {
    namespace video {
        Camera::Camera(glm::vec3 position, glm::vec3 worldUp) : m_Position(position),
                                                                m_WorldUp(worldUp) {
            m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
            m_Yaw = -90.0f;
            m_Pitch = 0.0f;
            m_MouseSensitivity = 10.00f;
            m_MovementSpeed = 2.5f;
            updateCameraVectors();
        }

        glm::mat4 Camera::getViewMatrix() {
            return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        }

        //TODO: We need to check if we are not in GUI
        void Camera::changeCameraPosition(float deltaTime) {
            if (r8ge::Input::isKeyPressed(r8ge::Key::MBUTTON_RIGHT)) {
                std::pair<double,double> temp;
                glfwSetInputMode(Video::getWindowingService()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                if (!m_bInputModeOn) {
                    temp = r8ge::Input::getMousePos();
                    m_lastX = temp.first;
                    m_lastY = temp.second;
                }
                m_bInputModeOn = true;
                temp = r8ge::Input::getMousePos();
                double mouseX = temp.first;
                double mouseY = temp.second;

                double mouseMoveX = (mouseX - m_lastX) * m_MouseSensitivity * deltaTime;
                double mouseMoveY = (m_lastY - mouseY) * m_MouseSensitivity * deltaTime;

                float velocity = m_MovementSpeed * deltaTime;

                if (r8ge::Input::isKeyPressed(r8ge::Key::W))
                    m_Position += m_Front * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::S))
                    m_Position -= m_Front * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::A))
                    m_Position -= m_Right * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::D))
                    m_Position += m_Right * velocity;

                temp = r8ge::Input::getScrollPos();
                if (temp.second == 1 && m_MovementSpeed <= m_maxMovementSpeed) {
                    m_MovementSpeed += 1.0f;
                }
                else if (temp.second == -1 && m_MovementSpeed >= m_minMovementSpeed) {
                    m_MovementSpeed -= 1.0f;
                }
                std::cout << m_MovementSpeed << std::endl;

                m_Yaw += mouseMoveX;
                m_Pitch += mouseMoveY;

                if (m_Pitch > 89.0f)
                    m_Pitch = 89.0f;
                if (m_Pitch < -89.0f)
                    m_Pitch = -89.0f;

                updateCameraVectors();

                m_lastX = mouseX;
                m_lastY = mouseY;
            } else {
                m_lastX = 0;
                m_lastY = 0;
                glfwSetInputMode(Video::getWindowingService()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                m_bInputModeOn = false;
            }
        }

        void Camera::updateCameraVectors() {
            m_Front = glm::normalize(glm::vec3(
                cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)),
                sin(glm::radians(m_Pitch)),
                sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch))
            ));
            m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
            m_Up = glm::normalize(glm::cross(m_Right, m_Front));
        }
    } // r8ge
} // video
