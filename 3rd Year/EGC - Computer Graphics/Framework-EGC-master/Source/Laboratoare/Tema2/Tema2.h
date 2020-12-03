/*
	Grigore Lucian-Florin
	Grupa 336CA
	Elemente de Grafica pe Calculator
	Tema 2 - Skyroads
*/
#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <iostream>
#include <vector>
#include <math.h>

#define MAX_NO_PLATFORMS 1

enum CELL_TYPE {RED, YELLOW, ORANGE, GREEN};

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();
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

	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
	void Tema2::DrawUI();
	void Tema2::AnimatePlatforms();

protected:
	glm::vec3 player_color;
	glm::vec3 player_position;
	int no_visible_platforms;
	float platform_speed;
	glm::vec3 platform_pos;
};