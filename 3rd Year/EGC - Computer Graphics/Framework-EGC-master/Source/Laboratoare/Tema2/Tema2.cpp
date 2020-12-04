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

	// creating UI element
	{
		Mesh* mesh = new Mesh("indicator");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
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

	// generating initial platforms
	{
		for (int i = 0; i >= -650; i -= 50)
		{
			for (int j = -110; j <= 110; j += 55)
			{
				glm::vec3 pos = glm::vec3(j, 0, i);
				initial_platform_positions.push_back(pos);
			}
		}
	}

	// initialising variables
	{
		player_position = glm::vec3(.0f, .5f, -2.f);
		player_color = glm::vec3(.3f, .3f, .9f);
		no_visible_platforms = 0;
		platform_speed = 100;
		last_acc = 0;
		time_elapsed = .0f;
		move_left = move_right = false;
		is_third_person = true;
		is_jumping = false;
		player_lateral_speed = 10.f;
		player_last_x = .0f;
		fuel_percent = 1.f;
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
	// checking if we ran out of fuel
	if (fuel_percent == .0f)
	{
		exit(0);
	}

	// updating fuel level
	if ((int)time_elapsed > last_acc && time_elapsed >= 3)
	{
		last_acc = (int)time_elapsed;
		fuel_percent -= .01f;
	}

	// deciding the color of the indicator
	glm::vec3 color;
	if (fuel_percent >= 0.66f)
		color = glm::vec3(.0f, 1.f, .0f);
	else if (fuel_percent >= 0.33f)
		color = glm::vec3(.9f, .9f, .0f);
	else
		color = glm::vec3(.9f, .0f, .0f);

	// drawing outer rectangle
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, glm::vec3(4, 1.2f, -3.01));
	model_matrix = glm::scale(model_matrix, glm::vec3(.5f, 2.5f, .01f));
	RenderSimpleMesh(meshes["indicator"], shaders["ShaderTema2"], model_matrix, glm::vec3(.0f, .0f, .0f));

	// drawing inner rectangle
	model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, glm::vec3(4, (float) 1.2f - 1.25f * (1.f - fuel_percent), -3));
	model_matrix = glm::scale(model_matrix, glm::vec3(.5f, (float) 2.5f * fuel_percent, .01f));
	RenderSimpleMesh(meshes["indicator"], shaders["ShaderTema2"], model_matrix, color);
}

void Tema2::AnimatePlatforms(float deltaTimeSeconds)
{
	// generate new platforms
	if (no_visible_platforms < MAX_NO_PLATFORMS)
	{
		glm::vec3 pos = glm::vec3(.0f, .0f, -500.f);
		pos.x = 55 * (rand() % 5 - 2);
		bool collision = false;

		// checking for possible overlappings
		for (glm::vec3 p : platform_positions)
		{
			if (p.z <= pos.z + 50 && p.x == pos.x)
			{
				collision = true;
				break;
			}
		}

		if (!collision)
		{
			int simple_prob = rand() % 20;
			glm::vec3 color = platform_color_types[0];
			PLATFORM_TYPE type = platform_available_types[0];

			if (!simple_prob)
			{
				int rand_fact = rand() % 4 + 1;
				color = platform_color_types[rand_fact];
				type = platform_available_types[rand_fact];
			}

			platform_positions.push_back(pos);
			platform_colors.push_back(color);
			platform_types.push_back(type);
			++no_visible_platforms;
		}
	}

	// translating and drawing visible platforms
	for (int i = 0; i < platform_positions.size(); ++i)
	{
		glm::vec3 col = platform_colors.at(i);
		glm::vec3 pos = platform_positions.at(i);

		glm::mat4 model_matrix = glm::mat4(1);
		model_matrix = glm::scale(model_matrix, glm::vec3(.02f, 1.f, .08f));
		model_matrix = glm::translate(model_matrix, pos);
		RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, col);

		pos += glm::vec3(.0f, .0f, 1.f) * platform_speed * deltaTimeSeconds;
		platform_positions.at(i) = pos;
	}

	// translating initial platforms, if there are any
	if (!initial_platform_positions.empty())
	{
		for (int i = 0; i < initial_platform_positions.size(); ++i)
		{
			glm::vec3 pos = initial_platform_positions.at(i);
			glm::vec3 col = platform_color_types[0];

			glm::mat4 model_matrix = glm::mat4(1);
			model_matrix = glm::scale(model_matrix, glm::vec3(.02f, 1.f, .08f));
			model_matrix = glm::translate(model_matrix, pos);
			RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, col);

			pos += glm::vec3(.0f, .0f, 1.f) * platform_speed * deltaTimeSeconds;
			initial_platform_positions.at(i) = pos;
		}
	}

	// delete initial platforms that are out of viewing area
	if (!initial_platform_positions.empty())
	{
		for (int i = 0; i < initial_platform_positions.size(); ++i)
		{
			glm::vec3 pos = initial_platform_positions.at(i);

			if (pos.z >= 50)
			{
				initial_platform_positions.erase(initial_platform_positions.begin() + i);
				break;
			}
		}
	}

	// delete platforms that are out of viewing area
	for (int i = 0; i < platform_positions.size(); ++i)
	{
		glm::vec3 pos = platform_positions.at(i);

		if (pos.z >= 50)
		{
			platform_positions.erase(platform_positions.begin() + i);
			platform_colors.erase(platform_colors.begin() + i);
			platform_types.erase(platform_types.begin() + i);
			--no_visible_platforms;
			break;
		}
	}
}

void Tema2::AnimatePlayer(float deltaTimeSeconds)
{
	// moving player to the correct position based on keyboard input
	if (move_left)
	{
		player_position -= glm::vec3(1, 0, 0) * deltaTimeSeconds * player_lateral_speed;
		if (player_position.x <= player_last_x - 1.125)
		{
			move_left = false;
			player_position.x = player_last_x - 1.125;
		}
	}
	if (move_right)
	{
		player_position += glm::vec3(1, 0, 0) * deltaTimeSeconds * player_lateral_speed;
		if (player_position.x >= player_last_x + 1.125)
		{
			move_right = false;
			player_position.x = player_last_x + 1.125;
		}
	}
	if (is_jumping)
	{
		// TODO
	}

	// drawing player
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, player_position);
	RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color);
}

void Tema2::CheckBoundaries()
{
	// TODO
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
	time_elapsed += deltaTimeSeconds;

	// drawing user interface
	DrawUI();

	// drawing platforms
	AnimatePlatforms(deltaTimeSeconds);

	// drawing player
	AnimatePlayer(deltaTimeSeconds);

	// checking collisions
	CheckBoundaries();
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (window->KeyHold(GLFW_KEY_A) && player_position.x > -2.25 &&
		!(move_left || move_right))
	{
		move_left = true;
		player_last_x = player_position.x;
	}
	if (window->KeyHold(GLFW_KEY_D) && player_position.x < 2.25 &&
		!(move_left || move_right))
	{
		move_right = true;
		player_last_x = player_position.x;
	}
	if (window->KeyHold(GLFW_KEY_W) && platform_speed < 500)
	{
		platform_speed += 50 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_S) && platform_speed > 100)
	{
		platform_speed -= 50 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_C))
	{
		is_third_person = !is_third_person;
	}
	if (window->KeyHold(GLFW_KEY_SPACE) && !is_jumping)
	{
		is_jumping = true;
	}
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
