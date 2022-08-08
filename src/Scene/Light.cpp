//----------------------------------------------------------------------------------------
/**
 * \file       Light.cpp
 * \author     Richard Kvasnica
 * \brief      Definition of different types of light
*/
//----------------------------------------------------------------------------------------

#include "Light.hpp"

namespace kvasnric
{
	Light::Light(const glm::vec3& diffuse, const glm::vec3& specular)
		: m_Diffuse(diffuse), m_Specular(specular)
	{
	}

	PointLight::PointLight(const glm::vec3& pos, const glm::vec3& diffuse, const glm::vec3& specular, const glm::vec3& ambient, float atLinear, float atQuad, float intensity)
		: Light(diffuse, specular), m_Position(pos), m_Ambient(ambient)
		, m_AttenuationLinear(atLinear), m_AttenuationQuadratic(atQuad), m_Intensity(intensity)
	{
	}

	PointLight::PointLight(const glm::vec3& pos, const glm::vec3& diffuse, float specular, float ambient, float atLinear, float atQuad, float intensity)
		: Light(diffuse, glm::vec3(specular)), m_Position(pos), m_Ambient(ambient)
		, m_AttenuationLinear(atLinear), m_AttenuationQuadratic(atQuad), m_Intensity(intensity)
	{
	}

	SpotLight::SpotLight(const glm::vec3& pos, const glm::vec3& direction, const glm::vec3& diffuse, float specular, float inCutoff, float outCutoff, bool gazePoint)
		: Light(diffuse, glm::vec3(specular)), m_Position(pos)
		, m_Direction(gazePoint ? direction - pos : direction)
		, m_CutOffInner(glm::cos(glm::radians(inCutoff))), m_CutOffOuter(glm::cos(glm::radians(outCutoff)))
	{
	}

	SpotLight::SpotLight(const glm::vec3& pos, glm::vec3& direction, const glm::vec3& diffuse, const glm::vec3& specular, float inCutoff, float outCutoff, bool gazePoint)
		: Light(diffuse, specular), m_Position(pos)
		, m_Direction(gazePoint ? glm::normalize(direction - pos) : direction)
		, m_CutOffInner(glm::cos(glm::radians(inCutoff))), m_CutOffOuter(glm::cos(glm::radians(outCutoff)))
	{
	}

}
