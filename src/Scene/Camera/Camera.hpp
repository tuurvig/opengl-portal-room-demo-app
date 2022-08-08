//----------------------------------------------------------------------------------------
/**
 * \file       Camera.hpp
 * \author     Richard Kvasnica
 * \brief      Camera abstract declaration
 *
 * Basic functionality of a virtual camera
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <glm/glm.hpp>
#include <constants.hpp>

namespace kvasnric
{
	class Camera
	{
	public:
		Camera(
			const glm::vec3& pos = CAMERA_START,
			const glm::vec3& up = WORLD_UP,
			float yaw = CAMERA_YAW_DEFAULT,
			float pitch = CAMERA_PITCH_DEFAULT
		);
		
		Camera(const Camera&) = default;
		
		virtual ~Camera() = default;

		/**
		 * @returns view matrix by calling glm::lookAt function
		 */
		virtual glm::mat4 GetViewMatrix();

		/**
		 * Virtual function that reacts based on relative motion input.
		 */
		virtual void MouseMovement(const glm::vec2& offset);

		glm::mat4 GetProjectionMatrix( float width, float height, float near = NEAR_PLANE, float far = FAR_PLANE ) const;
		
		inline glm::vec3 GetPosition() const { return m_Position; }
		inline glm::vec3 GetViewDirection() const { return m_Front; }

		/**
		 * Sets a position of the camera
		 */
		void Teleport(const glm::vec3& pos);

		/**
		 * Sets new camera view direction vector
		 */
		void SetViewDirection(const glm::vec3& dir);
	protected:
		/**
		 * Updates front, right and up vector of the camera by current yaw and pitch angle
		 */
		virtual void UpdateCameraSpace();
		
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;
		glm::vec3 m_Right;

		float m_Yaw;
		float m_Pitch;
		float m_FOV;
	};
}
