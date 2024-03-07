#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"
#include "../../core/Input.h"
#include "../Video.h"

namespace r8ge
{
    namespace video
    {
        glm::mat4 Camera::getViewMatrix()
        {
            return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
        }

        //TODO: We need to check if we are not in GUI
        void Camera::changeCameraPosition(float deltaTime)
        {
            if (r8ge::Input::isKeyPressed(r8ge::Key::MBUTTON_RIGHT))
            {
                glfwSetInputMode(Video::getWindowingService()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                if (!m_bInputModeOn)
                {
                    glfwGetCursorPos(Video::getWindowingService()->getWindow(), &m_lastX, &m_lastY);
                }
                m_bInputModeOn = true;
                double mouseX, mouseY;
                glfwGetCursorPos(Video::getWindowingService()->getWindow(), &mouseX, &mouseY);

                float velocity = m_MovementSpeed * deltaTime;

                if (r8ge::Input::isKeyPressed(r8ge::Key::W))
                    m_Position += m_Front * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::S))
                    m_Position -= m_Front * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::A))
                    m_Position -= m_Right * velocity;
                if (r8ge::Input::isKeyPressed(r8ge::Key::D))
                    m_Position += m_Right * velocity;

                double mouseMoveX = (mouseX - m_lastX) * m_MouseSensitivity * deltaTime;
                double mouseMoveY = (mouseY - m_lastY) * m_MouseSensitivity * deltaTime;

                //m_lastX = mouseX ;
                //m_lastY = mouseY;

                m_Yaw += mouseMoveX;
                m_Pitch += mouseMoveY;

                if (m_Pitch > 89.0f)
                    m_Pitch = 89.0f;
                if (m_Pitch < -89.0f)
                    m_Pitch = -89.0f;

                updateCameraVectors();
            }
            else
            {
                glfwSetInputMode(Video::getWindowingService()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                m_bInputModeOn = false;
            }
        }

        void Camera::updateCameraVectors()
        {
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
