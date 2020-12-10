#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "Tema2Levels.h"

#define MAX_PLATFORM_SPEED 25
#define MIN_PLATFORM_SPEED 5

class Platforms {
public:
	Platforms()
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

	float Platforms::SpawnNextPlatforms(float, std::vector<glm::vec3>&);

	float Platforms::SpawnNextPlatforms(float, std::vector<glm::vec3>&, std::vector<glm::vec3>&,
		std::vector<PLATFORM_TYPE>&, std::vector<bool>&);
};
