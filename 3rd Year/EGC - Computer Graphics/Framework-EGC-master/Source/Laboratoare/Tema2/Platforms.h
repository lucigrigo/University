#ifndef _PLATFORMS_
#define _PLATFORMS_
#include "Tema2.h"

#define MAX_NO_PLATFORMS 1000
#define MAX_PLATFORM_SPEED 25
#define MIN_PLATFORM_SPEED 5

enum PLATFORM_TYPE
{
    BASIC,
    RED,
    YELLOW,
    ORANGE,
    GREEN
};

const PLATFORM_TYPE platform_available_types[5] = {
    PLATFORM_TYPE::BASIC,
    PLATFORM_TYPE::RED,
    PLATFORM_TYPE::YELLOW,
    PLATFORM_TYPE::ORANGE,
    PLATFORM_TYPE::GREEN};

const glm::vec3 platform_color_types[6] = {
    glm::vec3(.0f, .0f, .8f),
    glm::vec3(1.f, .0f, .0f),
    glm::vec3(1.f, 1.f, .0f),
    glm::vec3(1.f, .5f, .0f),
    glm::vec3(.0f, 1.f, .0f),
    glm::vec3(.55f, .0f, .55f)};

int SpawnNextPlatforms(int, std::vector<glm::vec3>);

int SpawnNextPlatforms(int, std::vector<glm::vec3>, std::vector<glm::vec3>,
                       std::vector<PLATFORM_TYPES>, std::vector<bool>);

#endif