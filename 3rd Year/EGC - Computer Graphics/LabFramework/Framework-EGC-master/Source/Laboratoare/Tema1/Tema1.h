/*
	Grigore Lucian-Florin
	Grupa 336CA
	Elemente de Grafica pe Calculator
	Tema 1 - Bow and arrow
*/
#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <iostream>
#include <vector>
#include <math.h>

#define BALLOON_RED_NAME "red_balloon"
#define BALLOON_YELLOW_NAME "yellow_balloon"
#define BALLOON_GREEN_NAME "green_balloon"
#define BALLOON_BLUE_NAME "blue_balloon"
#define BALLOON_YELLOW_COLOR glm::vec3(1.f, 1.f, 0)
#define BALLOON_RED_COLOR glm::vec3(1.f, 0, 0)
#define BALLOON_GREEN_COLOR glm::vec3(0.f, 1.f, 0.f)
#define BALLOON_BLUE_COLOR glm::vec3(0.f, 0.f, 1.f)
#define BLACK glm::vec3(0, 0, 0)
#define NO_TRIANGLES 100
#define MAX_NO_BALLOONS 50
#define BALLOON_SPEED 300.f
#define BOW_MOVEMENT_SPEED 550.f

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

	void CheckBoundaries();
	void SpawnBalloons();
	void Tema1::SpawnShurikens();
	void Tema1::ShootArrow(float);
	void Tema1::CreateBalloon(glm::vec3, std::string);

	glm::mat3 Tema1::Translate(float, float);
	glm::mat3 Tema1::Scale(float, float);
	glm::mat3 Tema1::Rotate(float);

protected:
	int no_visible_balloons;
	std::vector<std::string> balloon_type;
	glm::mat3 shuriken_matrix;
	bool is_shuriken_shot;
	int score;
	short no_lives;
	bool is_arrow_shot;
	float arrow_speed;
	float time_elapsed;
	float click_time, release_time;
	std::vector<bool> is_hit;
	std::vector<int> no_scales;
	float power_indicator_scale_factor;
	glm::mat3 power_indicator_matrix;
	bool is_charging_shot;
	int last_second;
	int last_display;
	float shot_time;
	float shuriken_x;
	float shuriken_y;
	std::vector<float> balloon_x;
	std::vector<float> balloon_y;
	float bow_x;
	float bow_y;
	float bow_rotation;
	float shot_rotation;
	float arrow_x;
	float arrow_y;
	bool is_shuriken_deflected;
	float shuriken_angle;
};