#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "Tema3Levels.h"

#define MAX_PLATFORM_SPEED 20
#define MIN_PLATFORM_SPEED 5

class T3_Platforms {
public:
	T3_Platforms()
	{
	}

	const enum PLATFORM_TYPE
	{
		BASIC,
		RED,
		YELLOW,
		ORANGE,
		GREEN
	};

	PLATFORM_TYPE platform_available_types[5];

	glm::vec3 platform_color_types[6];

	void initValues();

	float T3_Platforms::SpawnNextPlatforms(float, std::vector<glm::vec3>&);

	float T3_Platforms::SpawnNextPlatforms(float, std::vector<glm::vec3>&, std::vector<glm::vec3>&,
		std::vector<PLATFORM_TYPE>&, std::vector<bool>&);
};
