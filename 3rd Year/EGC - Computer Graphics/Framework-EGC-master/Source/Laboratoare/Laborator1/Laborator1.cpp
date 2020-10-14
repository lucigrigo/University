#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>

using namespace std;

// indexul tipului de element desenat pt obiectul care se schimba
int MYMESH_INDEX = 0;
// numele fisierelor prin care cicleaza
const string names[] = { "box.obj", "sphere.obj", "teapot.obj" };
// valori care sunt folosite in Update()
// -> culorile de stergere
// -> pozitia unui obiect care se poate misca
// -> pozitia obiectului care se roteste
float val_red, val_green, val_blue, val_alpha = 1, obj_x = 2.f, obj_y = 2.f, obj_z = -2, rot_obj_x = -2, rot_obj_y = -3;
// timpul petrecut de la pornirea programului (suma tuturor deltaTimeSeconds-urilor)
float time_alive = 0.f;
int t;

// Tip: enable for good fun (:
#define GOOD_FUN 0

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Mesh* second_mesh = new Mesh("sample_mesh");
		second_mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[second_mesh->GetMeshID()] = second_mesh;

		// objects to loop through
		Mesh* mymesh = new Mesh("mymesh");
		mymesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mymesh->GetMeshID()] = mymesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// BONUS DE LA MINE
	// schimba culoarea automat la fiecare 90 de cadre (:
	++t;
	if (t == 90 && GOOD_FUN) {
		val_red = (rand() % 255) / 255.f;
		val_green = (rand() % 255) / 255.f;
		val_blue = (rand() % 255) / 255.f;
		val_alpha = (rand() % 255) / 255.f;
		t = 0;
	}
	// sets the clear color for the color buffer
	glClearColor(val_red, val_green, val_blue, val_alpha);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// EX 2
	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));
	
	// BONUS
	time_alive += deltaTimeSeconds;
	rot_obj_x = 3 * cos(time_alive * 3);
	rot_obj_y = 3 * sin(time_alive * 3);
	// render 3rd object
	RenderMesh(meshes["sample_mesh"], glm::vec3(rot_obj_x, rot_obj_y, -1));

	// render 4th object (the one that is looped through)
	RenderMesh(meshes["mymesh"], glm::vec3(obj_x, obj_y, obj_z));
}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	// EX 5
	if (window->KeyHold(GLFW_KEY_W)) { obj_x -= deltaTime; }
	if (window->KeyHold(GLFW_KEY_A)) { obj_z -= deltaTime; }
	if (window->KeyHold(GLFW_KEY_S)) { obj_x += deltaTime; }
	if (window->KeyHold(GLFW_KEY_D)) { obj_z += deltaTime; }
	if (window->KeyHold(GLFW_KEY_E)) { obj_y += deltaTime; }
	if (window->KeyHold(GLFW_KEY_Q)) { obj_y -= deltaTime; }
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// EX 3
	if (key == GLFW_KEY_R) {
		val_red = (rand() % 255) / 255.f;
		val_green = (rand() % 255) / 255.f;
		val_blue = (rand() % 255) / 255.f;
		val_alpha = (rand() % 255) / 255.f;
	}
	// EX 4
	if (key == GLFW_KEY_F) {
		Mesh* new_mesh = new Mesh("mymesh");
		new_mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", names[MYMESH_INDEX]);
		meshes["mymesh"]->ClearData();
		free(meshes["mymesh"]);
		meshes["mymesh"] = new_mesh;
		MYMESH_INDEX = (MYMESH_INDEX + 1) % 3;
	}
};

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
