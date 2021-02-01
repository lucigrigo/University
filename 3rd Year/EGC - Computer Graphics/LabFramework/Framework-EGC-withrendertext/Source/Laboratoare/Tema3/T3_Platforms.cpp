#include "T3_Platforms.h"

void T3_Platforms::initValues()
{
	platform_available_types[0] = PLATFORM_TYPE::BASIC;
	platform_available_types[1] = PLATFORM_TYPE::RED;
	platform_available_types[2] = PLATFORM_TYPE::YELLOW;
	platform_available_types[3] = PLATFORM_TYPE::ORANGE;
	platform_available_types[4] = PLATFORM_TYPE::GREEN;

	platform_color_types[0] = glm::vec3(.0f, .0f, .8f);
	platform_color_types[1] = glm::vec3(1.f, .0f, .0f);
	platform_color_types[2] = glm::vec3(1.f, 1.f, .0f);
	platform_color_types[3] = glm::vec3(1.f, .5f, .0f);
	platform_color_types[4] = glm::vec3(.0f, 1.f, .0f);
	platform_color_types[5] = glm::vec3(.55f, .0f, .55f);
}

float T3_Platforms::SpawnNextPlatforms(float far_z,
	std::vector<glm::vec3>& positions)
{
	for (int i = 0; i >= -80; i -= 8) {
		for (int j = -4; j <= 4; j += 2) {
			glm::vec3 pos = glm::vec3(j, 0, i);
			positions.push_back(pos);
		}
	}

	return -80.f;
}

float T3_Platforms::SpawnNextPlatforms(float far_z,
	std::vector<glm::vec3>& positions,
	std::vector<glm::vec3>& colors,
	std::vector<T3_Platforms::PLATFORM_TYPE>& types,
	std::vector<bool>& it_affects)
{
	if (far_z <= -40.f)
		return far_z;
	
	int empty_row = (rand() % 3 == 0) ? 1 : 0;
	float final_z = far_z - 80.f - 8.f * empty_row;
	int level_no = rand() % 9 + 1;

	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (custom_t3_levels[level_no][i][j] >= 1) {
				int val = custom_t3_levels[level_no][i][j];

				float x = (j - 2) * 2.f;
				float z = far_z - 8.f * (i + 1 + empty_row);
				glm::vec3 pos = glm::vec3(x, 0, z);

				positions.push_back(pos);
				colors.push_back(platform_color_types[val - 1]);
				types.push_back(platform_available_types[val - 1]);
				it_affects.push_back(false);
			}
		}
	}

	return final_z;
}
