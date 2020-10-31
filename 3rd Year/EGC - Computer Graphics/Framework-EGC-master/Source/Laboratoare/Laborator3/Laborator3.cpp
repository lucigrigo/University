#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

float tx, ty, rx, sx = 1.f, sy = 1.f, proc_tx = 200.f, proc_sx = 0.5f, side_size, tx1, rx1;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner1 = glm::vec3(150, resolution.y / 2, 0);
	glm::vec3 corner2 = glm::vec3(150, resolution.y / 2 - 100, 0);
	glm::vec3 corner3 = glm::vec3(250, resolution.y / 2 + 100, 0);
	glm::vec3 corner4 = glm::vec3(100, 100, 0);
	float squareSide = 100;
	side_size = squareSide;

	// compute coordinates of square center
	//float cx = corner.x + squareSide / 2;
	//float cy = corner.y + squareSide / 2;

	Mesh* square1 = Object2D::CreateSquare("square1", corner1, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner2, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner3, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquare("square4", corner4, squareSide, glm::vec3(1, 0, 1));
	AddMeshToList(square4);
}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	/*
	* Patratul cu marginea verde se scaleaza.
	* Patratul rosu se indeparteaza de origine.
	* Patratul cu marginea albastra se roteste in jurul originii.
	*/
	glm::ivec2 resolution = window->GetResolution();
	if (tx > resolution.y || tx < 0) { // schimbam sensul patratului care executa translatia
		proc_tx *= -1;
	}
	if (sx > 4.f || sx < 0.5f) { // schimbam intre micsorare / marire scalarea patratului 2
		proc_sx *= -1;
	}
	tx += deltaTimeSeconds * proc_tx;
	// ty += deltaTimeSeconds * 20; // am folosit variabila asta cand am vrut sa translatez si pe diagonala
	sx += deltaTimeSeconds * proc_sx;
	sy += deltaTimeSeconds * proc_sx;
	rx += deltaTimeSeconds * 5;
	tx1 += deltaTimeSeconds * 20;
	rx1 += deltaTimeSeconds * -1;

	// TRANSLATARE DINTR-O PARTE IN ALTA SI INVERS
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(tx, 0);
	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	// PULSARE
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(150, resolution.y / 2 - 100);
	modelMatrix *= Transform2D::Scale(sx, sy);
	modelMatrix *= Transform2D::Translate(-150, -resolution.y / 2 + 100);
	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

	// ROTATIE IN JURUL CENTRULUI SAU
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(250 + side_size / 2, resolution.y / 2 + 100 + side_size / 2);
	modelMatrix *= Transform2D::Rotate(rx);
	modelMatrix *= Transform2D::Translate(-250 - side_size / 2, -resolution.y / 2 - 100 - side_size / 2);
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

	// BONUS
	/*modelMatrix = glm::mat3(1);
	glm::vec3 pos = meshes["square4"]->positions[0];
	modelMatrix *= Transform2D::Translate(tx1, 0);
	modelMatrix *= Transform2D::Translate(100 + pos.x, 100);
	modelMatrix *= Transform2D::Rotate(rx1);
	modelMatrix *= Transform2D::Translate(-100 - pos.x, -100);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);*/
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
