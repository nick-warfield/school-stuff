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
				glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f));

		glm::vec3 Position(void) const;
		glm::vec3 Front(void) const;
		glm::vec3 Up(void) const;
		glm::vec3 Right(void) const;

		glm::mat4 GetViewMatrix(void) const;

		void Move(const glm::vec3& Direction, float deltaTime);
		void MouseMovement(float MouseX, float MouseY, GLboolean constrainPitch = true);
		void Zoom(float yoffset);

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

		void calculateCamVectors(void);
};

#endif
