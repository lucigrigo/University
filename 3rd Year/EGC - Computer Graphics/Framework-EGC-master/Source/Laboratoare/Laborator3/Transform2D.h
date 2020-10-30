#pragma once

#include <include/glm.h>

namespace Transform2D
{
	// Translate matrix
	inline glm::mat3 Translate(float translateX, float translateY)
	{
		// TODO implement translate matrix
		return glm::transpose(
					glm::mat3(1, 0, translateX,
							  0, 1, translateY,
							  0, 0, 1)
			);
	}

	// Scale matrix
	inline glm::mat3 Scale(float scaleX, float scaleY)
	{
		// TODO implement scale matrix
		return glm::transpose(
					glm::mat3(scaleX, 0, 0,
							  0, scaleY, 0,
							  0, 0, 1)
		);
	}

	// Rotate matrix
	inline glm::mat3 Rotate(float radians)
	{
		// TODO implement rotate matrix
		float degrees = radians * 180 / AI_MATH_PI;
		return glm::transpose(
					glm::mat3(cos(degrees), -sin(degrees), 0,
						      sin(degrees), cos(degrees), 0,
						      0, 0, 1)
		);
	}
}
