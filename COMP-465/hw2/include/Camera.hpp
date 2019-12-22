#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

class Camera
{
	public:
		Camera( glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 Rotation = glm::vec3(0.0f, -90.0f, 0.0f),
				glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f)) :
			m_position(Position),
			m_rotation(Rotation),
			m_worldUp(WorldUp),
			m_speed(2.5f),
			m_mouseSensitivity(0.1f),
			m_zoom(45.0f)
		{
			calculateCamVectors();
		}

		glm::vec3 Position(void) { return m_position; }
		glm::vec3 Front(void) { return m_front; }
		glm::vec3 Up(void) { return m_up; }
		glm::vec3 Right(void) { return m_right; }

		glm::mat4 GetViewMatrix(void)
		{
			return glm::lookAt(m_position, m_position + m_front, m_up);
		}

		void Move(glm::vec3 Direction, float deltaTime)
		{
			m_position += glm::normalize(Direction) * m_speed * deltaTime;
		}

		void MouseMovement(float MouseX, float MouseY, GLboolean constrainPitch = true)
		{
			MouseX *= m_mouseSensitivity;
			MouseY *= m_mouseSensitivity;

			m_rotation.y += MouseX;
			m_rotation.x += MouseY;

			if (constrainPitch)
			{
				if (m_rotation.x > 89.0f) { m_rotation.x = 89.0f; }
				if (m_rotation.x < -89.0f) { m_rotation.x = -89.0f; }
			}

			calculateCamVectors();
		}

		void Zoom(float yoffset)
		{
			m_zoom -= yoffset;
			if (m_zoom < 1.0f) { m_zoom = 1.0f; }
			if (m_zoom > 45.0f) { m_zoom = 45.0f; }
		}


	private:
		glm::vec3 m_position;
		glm::vec3 m_rotation;	// pitch, yaw, roll

		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;

		float m_speed;
		float m_mouseSensitivity;
		float m_zoom;

		void calculateCamVectors(void)
		{
			m_front = glm::normalize(glm::vec3(
						cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x)),
						sin(glm::radians(m_rotation.x)),
						sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x)) ));
			m_right = glm::normalize(glm::cross(m_front, m_worldUp));
			m_up = glm::normalize(glm::cross(m_right, m_front));
		}
};

#endif
