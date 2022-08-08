//----------------------------------------------------------------------------------------
/**
 * \file       constants.hpp
 * \author     Richard Kvasnica
 * \brief      Constants used in the entire program
*/
//----------------------------------------------------------------------------------------

#pragma once

#include "glm/glm.hpp"

namespace kvasnric
{
	// default world xyz axis
	const glm::vec3 X_AXIS(1.0f, 0.0f, 0.0f);
	const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);
	const glm::vec3 Z_AXIS(0.0f, 0.0f, 1.0f);

	// zero vectors 
	const glm::vec3 ZERO_VECTOR(0.0f, 0.0f, 0.0f);
	const glm::vec2 ZERO_VEC2(0.0f, 0.0f);

	const glm::vec3 ORIGIN(0.0f, 0.0f, 0.0f);
	const glm::mat4 UNIT_MATRIX(1.0f);

	// camera default values
	const float CAMERA_HEIGHT = 1.75f;
	const float CAMERA_SENSITIVITY = 0.1f;
	const float CAMERA_PITCH_DEFAULT = 0.0f;
	const float CAMERA_PITCH_CONSTRAINT = glm::radians(88.0f);
	const float CAMERA_YAW_DEFAULT = -90.0f;
	const float CAMERA_FOV_MAX = 80.0f;
	const float CAMERA_FOV_MIN = 1.0f;
	const float CAMERA_FOV_DEFAULT = 60.0f;
	const float CAMERA_FOV_35MM = 46.0f;

	// defines the default camera position and look direction
	const glm::vec3 CAMERA_START(0.0f, CAMERA_HEIGHT, 0.0f);
	const glm::vec3 CAMERA_FRONT(0.0f, 0.0f, -1.0f);

	const float MOVEMENT_SPEED = 3.0f;

	const float NEAR_PLANE = 0.05f;
	const float FAR_PLANE = 500.f;

	const glm::vec3 WORLD_UP(0.0f, 1.0f, 0.0f);
	const glm::vec3 WORLD_RIGHT(1.0f, 0.0f, 0.0f);

	// shader locations of vertex array attributes
	const short POSITION_LOC = 0;
	const short NORMAL_LOC = 1;
	const short TEX_COORD_LOC = 2;
	const short TANGENT_LOC = 3;

}
