#include "Laborator2.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include <math.h>

using namespace std;
#define NUM_TRIANGLES 72

Laborator2::Laborator2()
{
}

Laborator2::~Laborator2()
{

}

void Laborator2::Init()
{
	cullFace = GL_BACK;
	polygonMode = GL_FILL;

	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// Create a mesh box using custom data
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(1, 0,  0), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(0, 0,  1), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(-1, 0, -1), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(0, 2,  0), glm::vec3(1, 1, 0))
		};

		vector<unsigned short> indices =
		{
			0, 3, 1,
			1, 3, 2,
			2, 3, 0,
			0, 1, 2,
		};

		// Create a new mesh from buffer data
		Mesh * tetrahedron = CreateMesh("tetrahedron1", vertices, indices);

		meshes["tetrahedron1"] = tetrahedron;
	}

	// create a square using two triangles
	{
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(1, 2,  0), glm::vec3(0, 0, 1)),
			VertexFormat(glm::vec3(3, 2,  0), glm::vec3(0, 1, 1)),
			VertexFormat(glm::vec3(1, 0, 0), glm::vec3(1, 0, 1)),
			VertexFormat(glm::vec3(3, 0,  0), glm::vec3(1, 1, 0))
		};

		vector<unsigned short> indices =
		{
			0, 1, 2,
			1, 2, 3,
		};

		meshes["square1"] = new Mesh("generated square 1");
		meshes["square1"]->InitFromData(vertices, indices);
	}

	// create circle using triangles
	{
		vector<VertexFormat> vertices;
		vector<GLushort> indices;
		float arg;

		vertices.emplace_back(glm::vec3(0, 0, 0), glm::vec3(1, 1, 0));
		for (GLushort i = 0; i < NUM_TRIANGLES; i++)
		{
			arg = 2 * M_PI * i / NUM_TRIANGLES;

			vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), glm::vec3(1, 1, 0));
			indices.push_back(i);
		}
		indices.push_back(NUM_TRIANGLES);
		indices.push_back(1);

		meshes["circle"] = new Mesh("generated circle 1");
		meshes["circle"]->InitFromData(vertices, indices);
		meshes["circle"]->SetDrawMode(GL_TRIANGLE_FAN);
	}
}

Mesh* Laborator2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create the VBO and bind it
	unsigned int VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Unbind the VAO
	glBindVertexArray(0);

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

void Laborator2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	// Enable face culling
	glEnable(GL_CULL_FACE);

	// Set face custom culling. Use the "cullFace" variable
	glCullFace(cullFace);

	// render an object using face normals for color
	RenderMesh(meshes["box"], shaders["VertexNormal"], glm::vec3(0, 0.5f, -1.5f), glm::vec3(0.75f));

	// render an object using colors from vertex
	RenderMesh(meshes["tetrahedron1"], shaders["VertexColor"], glm::vec3(0.f, 0.f, 0.f));

	RenderMesh(meshes["square1"], shaders["VertexColor"], glm::vec3(0.f, 0.f, 0.f));

	RenderMesh(meshes["circle"], shaders["VertexColor"], glm::vec3(0.f, 2.f, 1.5f));

	// Disable face culling
	glDisable(GL_CULL_FACE);
}

void Laborator2::FrameEnd()
{
	DrawCoordinatSystem();
}

void Laborator2::OnInputUpdate(float deltaTime, int mods)
{

}

void Laborator2::OnKeyPress(int key, int mods)
{
	// switch between GL_FRONT and GL_BACK culling
	// Save the state in "cullFace" variable and apply it in the Update() method not here
	if (key == GLFW_KEY_F2)
	{
		cullFace = cullFace ^ GL_BACK ^ GL_FRONT;
	}

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
}

void Laborator2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator2::OnWindowResize(int width, int height)
{
}
