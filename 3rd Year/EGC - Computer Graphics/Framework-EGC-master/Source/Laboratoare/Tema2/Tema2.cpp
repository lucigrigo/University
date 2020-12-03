/*
	Grigore Lucian-Florin
	Grupa 336CA
	Elemente de Grafica pe Calculator
	Tema 2 - Skyroads
*/
#include "Tema2.h"

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	// creating UI elements
	{
		// TODO
	}
	
	// creating sphere (player)
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// creating platform model
	{
		Mesh* mesh = new Mesh("platform");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "plane50.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// creating shader
	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	// init variables
	{
		player_position = glm::vec3(.0f, .5f, -2.f);
		player_color = glm::vec3(.4f, .5f, .8f);
		no_visible_platforms = 0;
		platform_speed = .5f;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(.2f, .2f, .2f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::DrawUI() 
{
	// TODO
}

void Tema2::AnimatePlatforms() {
	// TODO
	if (no_visible_platforms < MAX_NO_PLATFORMS) {
		// generate new platforms
		platform_pos = glm::vec3(.0f, .0f, -1000.f);
		++no_visible_platforms;
	}
	
	// translate existing platforms
	platform_pos += glm::vec3(.0f, .0f, 1.f) * platform_speed;

	// draw visible platforms
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix = glm::scale(model_matrix, glm::vec3(.02f, .02f, .02f));
	model_matrix = glm::translate(model_matrix, platform_pos);
	RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, glm::vec3(.0f, 1.f, .0f));

	// delete platforms that are out of screen
	if (platform_pos.z >= 15) {
		--no_visible_platforms;
	}
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& model_matrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);

	GLint obj_color = glGetUniformLocation(shader->program, "object_color");
	glUniform3fv(obj_color, 1, glm::value_ptr(color));

	GLint model_location = glGetUniformLocation(shader->GetProgramID(), "Model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model_matrix));

	GLint view_location = glGetUniformLocation(shader->GetProgramID(), "View");
	glm::mat4 view_matrix = GetSceneCamera()->GetViewMatrix();
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view_matrix));

	GLint projection_location = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glm::mat4 projection_matrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::Update(float deltaTimeSeconds)
{
	// drawing user interface
	DrawUI();

	// drawing platforms
	AnimatePlatforms();

	// drawing player
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, player_position);
	RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color);
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem();
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema2::OnKeyPress(int key, int mods)
{
}

void Tema2::OnKeyRelease(int key, int mods)
{
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
