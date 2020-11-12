#include "Tema1.h"
#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	// setting camera position
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// init bow
	{
		Mesh* bow = new Mesh("bow");

		int m_y = resolution.y / 2;
		bow_line_pos0 = glm::vec3(100, m_y + 75, 0);
		bow_line_pos1 = glm::vec3(100, m_y - 75, 0);

		vector<VertexFormat> vertices {
			VertexFormat(bow_line_pos0, BLACK),
			VertexFormat(bow_line_pos1, BLACK)
		};

		vector<unsigned short> indices = {
			0, 1
		};

		bow->SetDrawMode(GL_LINES);
		bow->InitFromData(vertices, indices);
		AddMeshToList(bow);
	}

	// init balloon
	{
		// TODO: add coada la balon
		no_visible_balloons = 0;
		Mesh* balloon = new Mesh("balloon");

		vector<VertexFormat> vertices;
		vector<unsigned short> indices;

		vertices.emplace_back(glm::vec3(0, 0, 0), BLACK);
		for (unsigned short i = 0; i < NO_TRIANGLES; i++)
		{
			float arg = 2 * M_PI * i / NO_TRIANGLES;

			vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), BLACK);
			indices.push_back(i);
		}
		indices.push_back(NO_TRIANGLES);
		indices.push_back(1);

		balloon->InitFromData(vertices, indices);
		balloon->SetDrawMode(GL_TRIANGLE_FAN);
		AddMeshToList(balloon);
	}

	// TODO: init shuriken
}

void Tema1::FrameStart()
{
	// setting drawing area
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

	// we clear the color buffer
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema1::Update(float deltaTimeSeconds)
{
	// TODO: update score every few seconds
	// TODO: display score and lives remaining
	// TODO: check for collisions between balloons and arrow 
	// TODO: scale balloons down to 0 if they are hit

	// setting drawing area
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

	// we clear the color buffer
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(5);
	glPointSize(5);

	// drawing the bow
	glm::mat3 bow_line_matrix = glm::mat3(1);
	// TODO: apply rotation according to mouse position
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], bow_line_matrix);

	if (no_visible_balloons < MAX_NO_BALLOONS) {
		// TODO: generate random positions for balloons to spawn
	}

	// drawing visible balloons
	for (int i = 0; i < no_visible_balloons; ++i) {
		// TODO: delete from list balloons that are not visible anymore
		if (true) {
			;
		}
		RenderMesh2D(meshes["balloon"], shaders["VertexColor"], balloons_matrix[i]);
	}
}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Tema1::OnKeyPress(int key, int mods)
{
	
}

void Tema1::OnKeyRelease(int key, int mods)
{

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// TODO: rotate bow towards mouse position
	// cout << "mouseX = " << mouseX << " mouseY = " << mouseY << endl;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// TODO: adapt arrow speed
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// TODO: release arrow
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}

void Tema1::OnWindowResize(int width, int height)
{

}