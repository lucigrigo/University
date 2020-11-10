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
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// coordonatele initiale ale arcului
	bow_line_x0 = bow_line_x1 = resolution.x / 5;
	bow_line_y0 = resolution.y / 6;
	bow_line_y1 = 5 * resolution.y / 6;

	{
		vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(bow_line_y0, 0, bow_line_x0), glm::vec3(0, 1, 0)),
			VertexFormat(glm::vec3(bow_line_y1, 1, bow_line_x1), glm::vec3(0, 1, 0)),
		};
		std::vector<unsigned short> indices = { 0, 1 };

		simpleLine = new Mesh("line");
		simpleLine->InitFromData(vertices, indices);
		simpleLine->SetDrawMode(GL_LINES);
	}
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	simpleLine->Render();
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

}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{

}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{

}

void Tema1::OnWindowResize(int width, int height)
{

}