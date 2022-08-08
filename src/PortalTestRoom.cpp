//----------------------------------------------------------------------------------------
/**
 * \file       PortalTestRoom.cpp
 * \author     Richard Kvasnica
 * \brief      OpenGL application of portal test room declaration
*/
//----------------------------------------------------------------------------------------

#include "PortalTestRoom.hpp"

#include <iostream>
#include <cstdio>
#include <IO/Keyboard.hpp>
#include <IO/Mouse.hpp>

namespace kvasnric
{
	PortalTestRoom::PortalTestRoom()
		: OpenGLApplication( 1600, 900, "PortalTestRoom" ), m_PortalWalls( nullptr ), m_Iterations(1), m_Menu(nullptr)
	{
	}

	void PortalTestRoom::LoadResources()
	{
		m_Res.LoadEntityShader();
		m_Res.LoadCubeMapShader();
		m_Res.LoadCubeMap("gothic_alley");
		m_Res.LoadPortals();
		m_Res.LoadStencilStampTester();
		m_Menu.reset(new Menu(m_Res.GetTexture("menu.png", Texture2D::DIFFUSE), m_Res.GetTexture("cursor.png", Texture2D::SPECULAR), Width(), Height()));
		CheckErrors();
	}

	void PortalTestRoom::Setup()
	{
		SetupCameras();
		SetupLights();

		const glm::vec3 skycolor = glm::vec3(0.8f);

		SetClearColor(skycolor.r, skycolor.g, skycolor.b, 1.0f);
		m_Res.Entity().UploadSkyColor(skycolor);
		
		SetupModels();
		
		m_Blue.reset(new Portal(m_Res.GetTexture("portal_blue.png", Texture::DIFFUSE), { 0.0f,1.0f,-15.0f }, { 0.0f, 0.0f, 1.0f }));
		m_Orange.reset(new Portal(m_Res.GetTexture("portal_orange.png", Texture::DIFFUSE), { 0.0f,1.0f,-15.0f }, { 0.0f, 0.0f, -1.0f }));
	}

	void PortalTestRoom::SetupLights() const
	{
		PointLight l1(glm::vec3(-2.0f, 3.0f, -6.0f), glm::vec3(1.0f, 0.9f, 0.2f), 0.7f, 0.01f, 0.35f, 0.44f, 0.6f);
		PointLight l2(glm::vec3(2.0f, 3.0f, -6.0f), glm::vec3(0.1f, 0.2f, 1.0f), 0.65f, 0.02f, 0.35f, 0.44f, 0.7f);
		PointLight l3(glm::vec3(0.0f, 3.0f, -4.0f), glm::vec3(0.9f, 0.1f, 0.0f), 0.99f, 0.05f, 0.35f, 0.44f, 0.5f);

		SpotLight s1(glm::vec3(0.0f, 3.0f, -7.0f), glm::vec3(0.0f, 2.0f, -8.0f), glm::vec3(0.8f, 0.7f, 0.9f), 0.4f, 20.5f, 45.5f, true);
		SpotLight s2(glm::vec3(0.0f, 1.0f, -2.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.8f, 0.7f, 0.9f), 0.4f, 30.f, 60.f);

		SpotLight s3(glm::vec3(-5.0f, 4.0f, -13.0f), glm::vec3(0.0f, 4.5f, -15.0f), glm::vec3(0.9f, 0.2f, 0.1f), 0.4f, 15.f, 30.f, true);
		SpotLight s4(glm::vec3(5.0f, 4.0f, -13.0f), glm::vec3(0.0f, 4.5f, -15.0f), glm::vec3(0.1f, 0.4f, 0.9f), 0.4f, 15.f, 30.f, true);

		m_Res.Entity().Bind();
		m_Res.Entity().UploadPointLight(l1);
		m_Res.Entity().UploadPointLight(l2);
		m_Res.Entity().UploadPointLight(l3);

		m_Res.Entity().UploadSpotLight(s1);
		m_Res.Entity().UploadSpotLight(s2);
		m_Res.Entity().UploadSpotLight(s3);
		m_Res.Entity().UploadSpotLight(s4);
	}

	void PortalTestRoom::SetupModels()
	{
		m_Objects.emplace_back(m_Res["wheatley.obj"], glm::vec3{ 0.0f, 0.35f, -5.0f });

		m_Objects.emplace_back(m_Res["gothic.obj"], glm::vec3(1.0f, 0.0f, -5.0f));
		m_Objects.emplace_back(m_Res["gothic.obj"], glm::vec3(1.0f, 0.91f, -5.0f));
		m_Objects.back().Scale({ 0.6f, 0.6f, 0.6f });

		m_Objects.emplace_back(m_Res["gothic.obj"], glm::vec3(-1.0f, 0.0f, -5.0f));
		m_Objects.emplace_back(m_Res["gothic.obj"], glm::vec3(-1.0f, 0.91f, -5.0f));
		m_Objects.back().Scale({ 0.6f, 0.6f, 0.6f });

		m_Objects.emplace_back(m_Res["backpack.obj"], glm::vec3(-4.0f, 2.0f, -5.0f));
		m_Objects.back().RotationYAxis(-90.0f);

		m_Objects.emplace_back(m_Res["aperture_sign.obj"], glm::vec3(4.0f, 2.0f, -15.0f));
		m_Objects.back().Scale(glm::vec3(0.01f, 0.01f, 0.01f));

		m_Objects.emplace_back(m_Res["earth.obj"], glm::vec3(0.0f, 2.0f, -10.0f));
		m_Objects.back().GetModel().GetMeshes()[0]->Export();
		
		std::vector<glm::vec3> points = {
			{-4.768676f, 5.708214f, -4.713191f},
			{-1.444324f, 1.900001f, 0.552242f},
			{3.610741f, 1.750002f, -2.532145f},
			{10.226067f, 1.750001f, -2.561681f},
			{13.978791f, 1.750001f, -6.398846f},
			{14.197656f, 3.896972f, -11.126340f},
			{14.372760f, 1.750001f, -19.485508f},
			{10.404376f, 1.750001f, -23.865780f},
			{3.971180f, 1.750001f, -23.906567f},
			{-1.752727f, 4.339311f, -23.938444f},
			{-5.346721f, 4.542591f, -19.348381f},
			{-5.865470f, 3.042348f, -12.525190f}
		};

		const auto s = std::make_shared<Spline>(std::move(points));
		m_Wheatley.reset(new MovingObject(m_Res["wheatley.obj"], s));

		m_RoomWalls.reset(new GameObject(m_Res["scene_walls.obj"], ZERO_VECTOR));
		m_RoomFloor.reset(new GameObject(m_Res["scene_floor.obj"], ZERO_VECTOR));
		m_BloomLabel.reset(new GameObject(m_Res["scene_test_label.obj"], ZERO_VECTOR));
		m_Transparent.reset(new GameObject(m_Res["cube3.obj"], { 5.0f, 2.0f, -8.0f }));

		m_PortalWalls.reset(new PortalWalls(
			m_Res.GetTexture("concrete_diff.jpg", Texture::DIFFUSE),
			m_Res.GetTexture("concrete_spec.jpg", Texture::SPECULAR),
			m_Res.GetTexture("concrete_Normal.jpg", Texture::NORMAL),
			m_Res.GetTexture("concrete_rough.jpg", Texture::ROUGHNESS),
			m_Res.GetTexture("concrete_AO.jpg", Texture::OCCLUSION)
		));
	}

	void PortalTestRoom::SetupCameras()
	{
		m_Camera.reset(new FirstPersonCamera());

		m_Static1.reset(new Camera({ -4.418214f, 1.75f, -0.937762f }, WORLD_UP, -55.0f, 5.0f));
		m_Static2.reset(new Camera({ 15.497396f, 1.75f, -18.873907f }, WORLD_UP, 155.0f, 10.0f));
		m_ActiveCamera = m_Camera.get();

		m_View = m_ActiveCamera->GetViewMatrix();

		std::vector<glm::vec3> points = {
			{0.031416f, 1.750001f, -4.499891f},
			{0.070036f, 1.750001f, -10.031750f},
			{0.103651f, 1.772488f, -14.846611f},
			{-2.504439f, -3.249999f, -15.493988f},
			{-4.597615f, -3.249999f, -10.301954f},
			{1.292968f, -3.249999f, -9.238273f},
			{8.378442f, -3.249999f, -9.240015f},
			{12.149879f, -0.552531f, -13.849930f},
			{12.839034f, 1.750001f, -20.623253f},
			{7.716841f, 1.750001f, -23.598469f},
			{-0.338262f, 1.750001f, -23.569040f},
			{-5.510197f, 1.750001f, -21.248037f},
			{-5.343359f, 5.251458f, -15.016928f},
			{-5.282048f, 1.294905f, -10.001380f},
			{1.203391f, 1.750001f, -5.936583f},
			{11.676688f, 1.750001f, -4.544931f},
			{6.952653f, 1.750001f, -1.682285f},
			{0.000000f, 1.900001f, 0.000000f},
		};

		const auto s = std::make_shared<Spline>(std::move(points));
		m_Predefined.reset(new PredefinedCamera(s));
	}
	
	
	void PortalTestRoom::RenderScene() const
	{
		// render all the object that do not care about the the order of rendering
		const auto& entity = m_Res.Entity();
		entity.Bind();
		entity.RenderGameObject(*m_BloomLabel);

		entity.RenderGameObject(*m_Wheatley);
		
		for (auto & obj : m_Objects)
		{
			entity.RenderGameObject(obj);
		}
	}
	
	void PortalTestRoom::RenderInsidePortal(const Portal& p, const glm::mat4& view, const glm::mat4& projection,
		int stampId, int it) const
	{
		const auto& s = m_Res.Entity();

		/**
		 * teleportation matrix is applied from the right side of the view matrix so it will affect models from world coordinates first,
		 * but we want to compute lights first in the world coordinates
		 */
		const glm::mat4 portalView = view * p.GetTeleportation();
		const glm::vec3 position = p.Teleport(glm::vec4(m_ActiveCamera->GetPosition(), 1.0f));
		if( it == 1 )
		{
			StencilStamp::CompareToStamp(stampId);
			s.Bind();
			s.UploadViewInfo(position, portalView, projection);
			s.RenderPortalWalls(*m_PortalWalls);
			s.RenderGameObject(*m_RoomWalls);
			s.RenderGameObject(*m_RoomFloor);
			
			RenderScene();
		}
		else
		{
			// again firstly render a portal elipse into the stencil buffer and increase the stampId
			m_Res.Stencil().StampElements(p.GetVAO(), p.IndicesCount(), projection*portalView*p.GetModelMatrix(), stampId + 1);
			
			s.Bind();
			// render every wall and floor comparing to the stampId
			StencilStamp::CompareToStamp(stampId);
			s.UploadViewInfo(position, portalView, projection);
			s.RenderPortalWalls(*m_PortalWalls);
			s.RenderGameObject(*m_RoomWalls);
			s.RenderGameObject(*m_RoomFloor);

			// render scene over the portal
			StencilStamp::CheckInStamp(stampId);
			RenderScene();

			// recursively call another portal rendering
			RenderInsidePortal(p, portalView, projection, stampId + 1, it - 1);
		}

		StencilStamp::CheckInStamp(stampId);
		
		m_Res.PortalTexture().Render(p, m_CurrentTime, portalView, projection);

		if (m_Iterations == 1) StencilStamp::CompareToStamp(stampId);
		
		s.Bind();
		s.UploadViewInfo(position, portalView, projection);
		s.RenderTransparentGameObject(*m_Transparent);
	}

	void PortalTestRoom::Render()
	{
		Clear();
		m_View = m_ActiveCamera->GetViewMatrix();

		// render portal into stencil first
		const glm::mat4 pv = m_ActiveCamera->GetProjectionMatrix((float)Width(), (float)Height(), 0.01f, 500.0f) * m_View;
		m_Res.Stencil().StampElementsFirst(m_Blue->GetVAO(), m_Blue->IndicesCount(), pv*m_Blue->GetModelMatrix(), 1);
		m_Res.Stencil().StampElementsFirst(m_Orange->GetVAO(), m_Orange->IndicesCount(), pv*m_Orange->GetModelMatrix(), 10);
		
		const auto& s = m_Res.Entity();
		s.Bind();
		m_Res.Cubemap().Bind();
		s.UploadViewInfo(m_ActiveCamera->GetPosition(), m_View, m_Projection);
		StencilStamp::CompareToStamp(0);
		// if im under the ground update stencil buffer by the ground render
		if(m_ActiveCamera->GetPosition().y < 0.0f) StencilStamp::StampWithShader(0);
		// render floor
		s.RenderGameObject(*m_RoomFloor);
		StencilStamp::CompareToStamp(0);

		// render all walls by the stencil comparison, so nothing will override what is inside the portal
		s.RenderPortalWalls(*m_PortalWalls);
		s.RenderGameObject(*m_RoomWalls);

		// render the entire scene over the portal
		StencilStamp::CheckInStamp(0);
		RenderScene();

		// recursively render blue and orange portal
		RenderInsidePortal(*m_Blue, m_View, m_Projection, 1, m_Iterations);
		RenderInsidePortal(*m_Orange, m_View, m_Projection, 10, m_Iterations);

		// render skybox only to to the scene and first iterations of portal view
		if (!s.IsFogEnabled())
		{
			StencilStamp::CompareToStamp(10);
			const auto & cm = m_Res.CubemapShader();
			cm.Render(m_Res.Cubemap(), m_View*m_Orange->GetTeleportation(), m_Projection);
			StencilStamp::CompareToStamp(1);

			cm.Render(m_Res.Cubemap(), m_View*m_Blue->GetTeleportation(), m_Projection);
			StencilStamp::CompareToStamp(0);
			cm.Render(m_Res.Cubemap(), m_View, m_Projection);
		}

		// render transparent dynamic portal texture 
		StencilStamp::CheckInStamp(0);
		
		m_Res.PortalTexture().Render(*m_Blue, m_CurrentTime, m_View, m_Projection);
		m_Res.PortalTexture().Render(*m_Orange, m_CurrentTime, m_View, m_Projection);

		// finally render transparent object
		s.Bind();
		s.UploadViewInfo(m_ActiveCamera->GetPosition(), m_View, m_Projection);
		s.RenderTransparentGameObject(*m_Transparent);

		// if is menu active render the menu
		if (m_Menu->IsActive()) m_Menu->Render();
	}

	void PortalTestRoom::TimerUpdate()
	{
		// update the cursor or camera based on current relative mouse movement
		if (m_Menu->IsActive()) m_Menu->UpdateCursor(Mouse::GetRelativeMotion());
		else m_ActiveCamera->MouseMovement(Mouse::GetRelativeMotion());

		if (m_Camera.get() == m_ActiveCamera && !m_Menu->IsActive())
		{	
			auto previous = m_Camera->GetPosition();
			m_Camera->UpdatePosition(m_TimeDelta,
				Keyboard::IsLeftShiftPressed() ? MOVEMENT_SPEED * 2.0f : MOVEMENT_SPEED, previous.y,
				Keyboard::IsPressed(Keyboard::W),
				Keyboard::IsPressed(Keyboard::A),
				Keyboard::IsPressed(Keyboard::D),
				Keyboard::IsPressed(Keyboard::S)
			);
			// calculate new camera position and check whether the new position collides with portal
			HandlePortalCollision(previous);

			// then check the floor collision
			HandleFloorCollision(previous);
		}

		m_Wheatley->Update(m_CurrentTime);

		if (m_ActiveCamera == m_Predefined.get())
		{
			m_Predefined->Update(m_CurrentTime);
		}
	}
	
	void PortalTestRoom::HandleFloorCollision(const glm::vec3& previous)
	{
		const auto & newPos = m_Camera->GetPosition();

		for (const auto & mesh : m_RoomFloor->GetModel().GetMeshes())
		{
			glm::vec3 position, dummy;
			if (mesh->FindIntersection(position, dummy, newPos, { 0.0f, -1.0f, 0.0f }))
			{
				// if the intersection is found calculate free fall by the time delta
				float y = previous.y;

				y = m_Velocity * m_TimeDelta + y - 10 * m_TimeDelta * m_TimeDelta;
				m_Velocity = m_Velocity - 10 * m_TimeDelta;

				const float height = position.y + CAMERA_HEIGHT;
				if (y < height ) {
					y = height;
					m_Velocity = 0.0f;
				}
				
				m_LastOkLocation = position;
				m_Camera->Teleport({ newPos.x, y, newPos.z });
				return;
			}
		}
		// if no collision was found teleport the camera to the last ok location
		float y = previous.y;
		y = m_Velocity * m_TimeDelta + y - 10 * m_TimeDelta*m_TimeDelta;
		m_Velocity = m_Velocity - 10 * m_TimeDelta;

		const float height = m_LastOkLocation.y + CAMERA_HEIGHT;
		if (y < height && height - y < 0.1f) {
			y = height;
			m_Velocity = 0.0f;
		}
		
		m_Camera->Teleport({ m_LastOkLocation.x, y, m_LastOkLocation.z });
	}

	void PortalTestRoom::HandlePortalCollision(glm::vec3& pos) const
	{
		const auto current = m_Camera->GetPosition();

		// if im coliding with the portal, teleport camera to the different position of the scene.
		if (m_Blue->IsColliding(current))
		{
			pos = m_Blue->Teleport(glm::vec4(current, 1.0f));
			m_Camera->Teleport(pos);

			m_Camera->ChangeView(m_Blue->GetViewAngle());
			return;
		}

		if (m_Orange->IsColliding(current))
		{
			pos = m_Orange->Teleport(glm::vec4(current, 1.0f));
			m_Camera->Teleport(pos);

			m_Camera->ChangeView(m_Orange->GetViewAngle());
		}
	}

	void PortalTestRoom::MountCameraOnObject()
	{
		ClearDepth();
		const auto pv = m_Projection * m_View;
		const unsigned begin = 128;
		for (unsigned i = 0; i < m_Objects.size(); ++i)
		{
			const auto & obj = m_Objects[i];
			m_Res.Stencil().StampModel(obj.GetModel(), pv*obj.GetModelMatrix(), begin + i);
		}

		const unsigned id = StencilStamp::ReadStencilPixelValue(Width() >> 1, Height() >> 1);

		if (id < begin || !m_Objects[id - begin].IsInProximity(m_ActiveCamera->GetPosition(), 5.0f)) return;
		m_MountedCamera.reset(new MountedCamera(&m_Objects[id - begin]));
		m_ActiveCamera = m_MountedCamera.get();
	}

	

	void PortalTestRoom::MouseClick()
	{
		if (m_Menu->IsActive())
		{
			switch (m_Menu->Click())
			{
			case Menu::TOGGLE_FOG:
				m_Res.Entity().ToggleFog();
				break;
			case Menu::STATIC_1:
				m_ActiveCamera = m_Static1.get();
				break;
			case Menu::STATIC_2:
				m_ActiveCamera = m_Static2.get();
				break;
			case Menu::WHEATLEY:
				m_MountedCamera.reset(new MountedCamera(m_Wheatley.get()));
				m_ActiveCamera = m_MountedCamera.get();
				break;
			case Menu::EXIT_MENU:
				break;
			case Menu::QUIT_GAME:
				m_Run = false;
				return;
			case Menu::DEFAULT: return;
			}
			m_Menu->ToggleActive();
		}
		
		if(m_ActiveCamera == m_Camera.get())
		{
			glm::vec3 portalLocation(0);
			glm::vec3 normal(0);
			
			Portal * update = Mouse::IsLeft() ? m_Blue.get() : Mouse::IsRight() ? m_Orange.get() : nullptr;

			// check if the clicking does an intersection with portal walls, then update the portals accordingly.
			if(update != nullptr && m_PortalWalls->GetMeshes()[0]->FindIntersection( portalLocation, normal, m_Camera->GetPosition(), m_Camera->GetViewDirection()))
			{
				update->ModifyPortal(portalLocation, normal);
				const float angle = m_Blue->SetTeleporation(*m_Orange);
				m_Orange->SetTeleporation(*m_Blue);

				// set the number of iterations based on the angle between portals. In 45 degrees there is no way we could see third portal iteration.
				// if the angle is the same that mean we are able to see no recursive iteration
				if (angle < 0.000001f) m_Iterations = 1;
				else if (sin(angle) < 0.000001f) m_Iterations = 6;
				else m_Iterations = 2;
			}
		}
	}

	void PortalTestRoom::ResizeUpdate()
	{
		m_Projection = m_ActiveCamera->GetProjectionMatrix((float) Width(), (float) Height(), 0.05f, 500.0f);
		m_Menu->Resize(Width(), Height());
	}

	void PortalTestRoom::ReactOnKey()
	{
		if (!m_Menu->IsActive())
		{
			if (Keyboard::IsPressed(Keyboard::F)) {
				m_Res.Entity().ToggleFog();
			}

			if (m_ActiveCamera == m_Camera.get() && Keyboard::IsPressed(Keyboard::SPACE))
			{
				m_Velocity = 3.5f;
			}

			if (Keyboard::IsPressed(Keyboard::V) && (m_ActiveCamera == m_Static1.get() || m_ActiveCamera == m_Static2.get()))
			{
				m_Camera.reset(new FirstPersonCamera(*m_ActiveCamera));
				m_ActiveCamera = m_Camera.get();
			}

			if (Keyboard::IsPressed(Keyboard::M))
			{
				if (m_ActiveCamera != m_MountedCamera.get()) MountCameraOnObject();
				else
				{
					m_ActiveCamera = m_Camera.get();
				}
			}
		}
		
		if (Keyboard::IsPressed(Keyboard::ESC)) m_Menu->ToggleActive();
	}

	void PortalTestRoom::ReactOnSpecialKey()
	{
		if (!m_Menu->IsActive())
		{
			if (Keyboard::IsPressed(Keyboard::F1))
			{
				m_ActiveCamera = m_Static1.get();
				return;
			}

			if (Keyboard::IsPressed(Keyboard::F2))
			{
				m_ActiveCamera = m_Static2.get();
				return;
			}

			if (Keyboard::IsPressed(Keyboard::F6))
			{
				m_ActiveCamera = m_Camera.get();
				return;
			}

			if (Keyboard::IsPressed(Keyboard::F5))
			{
				m_Camera.reset(new FirstPersonCamera());
				m_ActiveCamera = m_Camera.get();
				return;
			}

			if (Keyboard::IsPressed(Keyboard::F3))
			{
				m_MountedCamera.reset(new MountedCamera(m_Wheatley.get()));
				m_ActiveCamera = m_MountedCamera.get();
				return;
			}

			if (Keyboard::IsPressed(Keyboard::F4))
			{
				m_ActiveCamera = m_Predefined.get();
				m_Predefined->Start(m_CurrentTime);
				return;
			}
		}
	}
}
