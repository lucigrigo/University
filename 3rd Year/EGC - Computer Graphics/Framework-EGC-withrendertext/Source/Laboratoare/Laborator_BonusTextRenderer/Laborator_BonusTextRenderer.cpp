#include "Laborator_BonusTextRenderer.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator_BonusTextRenderer::Laborator_BonusTextRenderer()
{
}

Laborator_BonusTextRenderer::~Laborator_BonusTextRenderer()
{
}

void Laborator_BonusTextRenderer::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Default fill objects
	polygonMode = GL_FILL;

	// Text renderer
	glm::ivec2 resolution = window->GetResolution();
	Text = new TextRenderer(resolution.x, resolution.y);

	Text->Load("Source/TextRenderer/Fonts/Arial.ttf", 18);
}

void Laborator_BonusTextRenderer::drawHud()
{
	Text->RenderText("Utilizare taste", 5.0f, 5.0f, 1.0f, glm::vec3(0.0, 1.0, 0.0));
	Text->RenderText("'space'  : Toggle Solid/Wireframe/Points", 5.0f, 25.0f, 1.0f, glm::vec3(0.0, 1.0, 0.0));

	std::string polygonModeText = "";
	if (polygonMode == GL_LINE)
		polygonModeText = "LINII";
	if (polygonMode == GL_FILL)
		polygonModeText = "SOLID";
	if (polygonMode == GL_POINT)
		polygonModeText = "PUNCTE";

	Text->RenderText("'z'  : Activare desenare cu LINII (mod curent " + polygonModeText + ")", 5.0f, 50.0f, 1.0f, glm::vec3(0.0, 1.0, 0.0));
	Text->RenderText("'x'  : Activare desenare cu PUNCTE (mod curent " + polygonModeText + ")", 5.0f, 75.0f, 1.0f, glm::vec3(0.0, 1.0, 0.0));
	Text->RenderText("'c'  : Activare desenare cu SOLID (mod curent " + polygonModeText + ")", 5.0f, 100.0f, 1.0f, glm::vec3(0.0, 1.0, 0.0));
}

void Laborator_BonusTextRenderer::FrameStart()
{

}

void Laborator_BonusTextRenderer::Update(float deltaTimeSeconds)
{
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(0, 0, 0, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

}

void Laborator_BonusTextRenderer::FrameEnd()
{
	drawHud();
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator_BonusTextRenderer::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
};

void Laborator_BonusTextRenderer::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
	// add key press event
	if (key == GLFW_KEY_Z) {
		polygonMode = GL_LINE;
	}
	// add key press event
	if (key == GLFW_KEY_X) {
		polygonMode = GL_POINT;
	}
	// add key press event
	if (key == GLFW_KEY_C) {
		polygonMode = GL_FILL;
	}
	// add key press event
	if (key == GLFW_KEY_F) {
		// do something
	}
};

void Laborator_BonusTextRenderer::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator_BonusTextRenderer::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator_BonusTextRenderer::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator_BonusTextRenderer::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator_BonusTextRenderer::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator_BonusTextRenderer::OnWindowResize(int width, int height)
{
	// treat window resize event
}
