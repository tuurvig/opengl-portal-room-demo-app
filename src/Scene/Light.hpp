//----------------------------------------------------------------------------------------
/**
 * \file       Light.hpp
 * \author     Richard Kvasnica
 * \brief      Declaration of different types of light
*/
//----------------------------------------------------------------------------------------

#pragma once

#include <glm/glm.hpp>

namespace kvasnric
{
	// LIGHT ABSTRACT
	////////////////////////////////////////////////////////////////////////////////////////

	
	// Abstract light class defining basic properties
	class Light
	{
	public:
		/**
		 * Light class constructor
		 * @param diffuse color of the light
		 * @param specular defines reflecting property of the light
		 */
		Light(const glm::vec3& diffuse, const glm::vec3& specular);
		virtual ~Light() = default;

		// setters 
		inline void SetDiffuse(const glm::vec3& diffuse) { m_Diffuse = diffuse; }
		inline void SetSpecular(const glm::vec3& specular) { m_Specular = specular; }
		inline void SetSpecular(float specular) { m_Specular = glm::vec3(specular); }

		// getters
		inline const glm::vec3& GetDiffuse() const { return m_Diffuse; }
		inline const glm::vec3& GetSpecular() const { return m_Specular; }
	protected:
		glm::vec3 m_Diffuse;
		glm::vec3 m_Specular;
	};

	// POINT LIGHT
	////////////////////////////////////////////////////////////////////////////////////////
	
	// class defining point light properties. Child class of light
	class PointLight final : public Light
	{
	public:
		/**
		 * Point light constructor.
		 * @param pos world position of the light
		 * @param diffuse lights color
		 * @param specular reflective property of the light
		 * @param ambient ambient light intensity property
		 * @param atLinear linear component of attenuation property
		 * @param atQuad quadratic component of attenuation property
		 * @param intensity intensity of the light
		 */
		PointLight(
			const glm::vec3& pos, const glm::vec3& diffuse, const glm::vec3& specular,
			const glm::vec3& ambient, float atLinear, float atQuad, float intensity);
		/**
		 * Same as the other constructor
		 */
		PointLight(
			const glm::vec3& pos, const glm::vec3& diffuse, float specular,
			float ambient, float atLinear, float atQuad, float intensity);

		// setters 
		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; }
		inline void SetAmbient(const glm::vec3& ambient) { m_Ambient = ambient; }
		inline void SetAmbient(float ambient) { m_Ambient = glm::vec3(ambient); }
		inline void SetAttenuation(float linear, float quadratic)
		{
			m_AttenuationLinear = linear; m_AttenuationQuadratic = quadratic;
		}
		inline void SetIntensity(float intensity) { m_Intensity = intensity; }

		// getters
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetAmbient() const { return m_Ambient; }
		inline glm::vec2 GetAttenuation() const
		{
			return glm::vec2(m_AttenuationLinear, m_AttenuationQuadratic);
		}
		inline float GetIntensity() const { return m_Intensity; }
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Ambient;
		float m_AttenuationLinear;
		float m_AttenuationQuadratic;
		float m_Intensity;
	};

	// SPOT LIGHT
	////////////////////////////////////////////////////////////////////////////////////////
	
	class SpotLight final : public Light
	{
	public:
		/**
		 * Spot light constructor.
		 * @param pos world position of the light
		 * @param direction direction of the light
		 * @param diffuse lights color
		 * @param specular reflective property of the light
		 * @param inCutoff inner angle of uninterrupted light
		 * @param outCutoff the absolute outer cutoff. No light will go out this angle
		 * @param gazePoint bool whether the direction vector is a direction or point of gaze 
		 */
		SpotLight(
			const glm::vec3& pos, glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular,
			float inCutoff, float outCutoff, bool gazePoint = false);
		/**
		 * Same as the other constructor
		 */
		SpotLight(
			const glm::vec3& pos, const glm::vec3& direction, const glm::vec3& diffuse, float specular,
			float inCutoff, float outCutoff, bool gazePoint = false );

		// setters
		inline void SetPosition(const glm::vec3& pos) { m_Position = pos; }
		inline void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
		inline void SetCutOff(float inner, float outer) { m_CutOffInner = inner; m_CutOffOuter = outer; }

		// getters
		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetDirection() const { return m_Direction; }
		inline glm::vec2 GetCutOff() const { return glm::vec2(m_CutOffInner, m_CutOffOuter); }
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		float m_CutOffInner;
		float m_CutOffOuter;
	};
}