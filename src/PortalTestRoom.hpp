//----------------------------------------------------------------------------------------
/**
 * \file       PortalTestRoom.hpp
 * \author     Richard Kvasnica
 * \brief      OpenGL application of portal test room declaration
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <OpenGLApplication.hpp>

#include <Scene/GameObject.hpp>
#include <Scene/MovingObject.hpp>
#include <Scene/Camera/FirstPersonCamera.hpp>
#include <Scene/Camera/MountedCamera.hpp>
#include <Scene/Camera/PredefinedCamera.hpp>

#include <Scene/PortalWalls.hpp>
#include <Portal.hpp>

#include <Menu.hpp>

namespace kvasnric
{
	// this opengl application acts as a scene of portal test room
	class PortalTestRoom final : public OpenGLApplication
	{
	public:
		PortalTestRoom();

		// overriden callbacks from the parent class. Is called by GLUTWrapper
		void Setup() override;
		void Render() override;
		void TimerUpdate() override;
		void MouseClick() override;
		void ResizeUpdate() override;
		void ReactOnKey() override;
		void ReactOnSpecialKey() override;
		void LoadResources() override;
	private:
		/**
		 * Renders every "safe" object in the scene.
		 * 
		 */
		void RenderScene() const;

		/**
		 * Recursively rendering a scene inside a portal. Limited by the number of iterations
		 */
		void RenderInsidePortal(const Portal& p, const glm::mat4& view, const glm::mat4& projection, int stampId, int it) const;

		/**
		 * Calls Meshes ability to detect intersection with the floor and return it.
		 * Also teleports camera back onto the colliding floor if no collision was detected.
		 */
		void HandleFloorCollision(const glm::vec3& previous);

		/**
		 * Detection of camera view vector with portal wall mesh.
		 * Intersection is used for updating the portal
		 */
		void HandlePortalCollision(glm::vec3& pos) const;

		/**
		 * Draws picking objects into stencil buffer. Reads the value from the stencil buffer and
		 * locks camera on this object.
		 */
		void MountCameraOnObject();

		// divides scene setup into groups
		void SetupLights() const;
		void SetupModels();
		void SetupCameras();
		
		std::vector<GameObject> m_Objects;
		std::unique_ptr<GameObject> m_Transparent;
		
		std::unique_ptr<GameObject> m_RoomWalls;
		std::unique_ptr<GameObject> m_RoomFloor;
		std::unique_ptr<GameObject> m_BloomLabel;
		
		std::unique_ptr<MovingObject> m_Wheatley;
		
		std::unique_ptr<PortalWalls> m_PortalWalls;
		
		std::unique_ptr<FirstPersonCamera> m_Camera;
		std::unique_ptr<MountedCamera> m_MountedCamera;
		std::unique_ptr<PredefinedCamera> m_Predefined;
		std::unique_ptr<Camera> m_Static1;
		std::unique_ptr<Camera> m_Static2;
		
		Camera* m_ActiveCamera;
		
		glm::mat4 m_Projection;
		glm::mat4 m_View;

		glm::vec3 m_LastOkLocation;
		float m_Velocity;
		
		std::unique_ptr<Portal> m_Blue;
		std::unique_ptr<Portal> m_Orange;
		int m_Iterations;

		std::unique_ptr<Menu> m_Menu;
	};
}