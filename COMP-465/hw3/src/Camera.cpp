#include "../include/Camera.hpp"

Camera::Camera(
		glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 WorldUp) :
	m_position(Position),
	m_rotation(Rotation),
	m_worldUp(WorldUp),
	m_speed(2.5f),
	m_mouseSensitivity(0.1f),
	m_zoom(45.0f)
{
	calculateCamVectors();
}

glm::vec3 Camera::Position(void) const { return m_position; }
glm::vec3 Camera::Front(void) const { return m_front; }
glm::vec3 Camera::Up(void) const { return m_up; }
glm::vec3 Camera::Right(void) const { return m_right; }

glm::mat4 Camera::GetViewMatrix(void) const
{
	return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::Move(const glm::vec3& Direction, float deltaTime)
{
	m_position += glm::normalize(Direction) * m_speed * deltaTime;
}

void Camera::MouseMovement(float MouseX, float MouseY, GLboolean constrainPitch)
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

void Camera::Zoom(float yoffset)
{
	m_zoom -= yoffset;
	if (m_zoom < 1.0f) { m_zoom = 1.0f; }
	if (m_zoom > 45.0f) { m_zoom = 45.0f; }
}

void Camera::calculateCamVectors(void)
{
	m_front = glm::normalize(glm::vec3(
				cos(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x)),
				sin(glm::radians(m_rotation.x)),
				sin(glm::radians(m_rotation.y)) * cos(glm::radians(m_rotation.x)) ));
	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}
