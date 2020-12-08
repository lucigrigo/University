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
		for (float i = -0; i >= -40; i -= 4)
			// for (int i = 0; i >= -650; i -= 50)
		{
			for (float j = -2.1f; j <= 2.1f; j += 1.05f)
				// for (int j = -110; j <= 110; j += 55)
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
		platform_speed = MIN_PLATFORM_SPEED;
		last_acc = 0;
		time_elapsed = .0f;
		move_left = move_right = false;
		is_third_person = true;
		is_jumping = false;
		player_lateral_speed = 8.f;
		player_last_x = .0f;
		fuel_percent = 1.f;
		orange_platform_start = 0;
		is_affected_orange_plat = false;
		last_speed = MIN_PLATFORM_SPEED;
		is_falling = false;
		player_jump_speed = 1.f;
	}
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(.25f, .25f, .25f, .9f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::DrawUI(float deltaTimeSeconds)
{
	// checking if we ran out of fuel
	if (fuel_percent <= .0f)
		AnimateFall(deltaTimeSeconds);

	// updating fuel level
	if ((int)time_elapsed > last_acc && time_elapsed >= 3 && !is_affected_orange_plat)
	{
		last_acc = (int)time_elapsed;
		fuel_percent -= .001f * platform_speed;
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
	RenderSimpleMesh(meshes["indicator"], shaders["ShaderTema2"], model_matrix, glm::vec3(.0f, .0f, .0f), false);

	// drawing inner rectangle
	model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, glm::vec3(4, (float)1.2f - 1.25f * (1.f - fuel_percent), -3));
	model_matrix = glm::scale(model_matrix, glm::vec3(.5f, (float)2.5f * fuel_percent, .01f));
	RenderSimpleMesh(meshes["indicator"], shaders["ShaderTema2"], model_matrix, color, false);
}

void Tema2::AnimatePlatforms(float deltaTimeSeconds)
{
	if (is_falling)
		return;

	// generate new platforms
	if (no_visible_platforms < MAX_NO_PLATFORMS)
	{
		glm::vec3 pos = glm::vec3(.0f, .0f, -40.f);
		pos.x = 1.05 * (rand() % 5 - 2);
		bool collision = false;

		// checking for possible overlappings
		for (glm::vec3 p : platform_positions)
		{
			if (p.z <= pos.z + 4.01 && p.x == pos.x)
			{
				collision = true;
				break;
			}
		}

		if (!collision)
		{
			int simple_prob = rand() % 50;
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
			affects_player.push_back(false);
			++no_visible_platforms;
		}
	}

	// translating and drawing visible platforms
	for (int i = 0; i < platform_positions.size(); ++i)
	{
		glm::vec3 col = platform_colors.at(i);
		glm::vec3 pos = platform_positions.at(i);

		glm::mat4 model_matrix = glm::mat4(1);
		model_matrix = glm::translate(model_matrix, pos);
		model_matrix = glm::scale(model_matrix, glm::vec3(.02f, 1.f, .08f));
		RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, col, false);

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
			model_matrix = glm::translate(model_matrix, pos);
			model_matrix = glm::scale(model_matrix, glm::vec3(.02f, 1.f, .08f));
			RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, col, false);

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

			if (pos.z >= 3)
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

		if (pos.z >= 3)
		{
			platform_positions.erase(platform_positions.begin() + i);
			platform_colors.erase(platform_colors.begin() + i);
			platform_types.erase(platform_types.begin() + i);
			affects_player.erase(affects_player.begin() + i);
			--no_visible_platforms;
			break;
		}
	}
}

void Tema2::AnimateFall(float deltaTimeSeconds)
{
	is_falling = true;

	if (player_position.y <= -6.f)
		exit(0);

	for (int i = 0; i < platform_positions.size(); ++i) {
		glm::vec3 col = platform_colors.at(i);
		glm::vec3 pos = platform_positions.at(i);
		pos += glm::vec3((rand() % 3 - 1) * 1.f, (rand() % 3 - 1) * 1.f, .0f) * (float)MIN_PLATFORM_SPEED * deltaTimeSeconds;

		if (pos.z >= -3)
			continue;

		glm::mat4 model_matrix = glm::mat4(1);
		model_matrix = glm::translate(model_matrix, pos);
		model_matrix = glm::scale(model_matrix, glm::vec3(.02f, 1.f, .08f));
		RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, col, false);
	}

	player_position -= glm::vec3(.0f, .8f, .4f) * deltaTimeSeconds * (float)MIN_PLATFORM_SPEED;
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, player_position);
	RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color, false);
}

void Tema2::AnimatePlayer(float deltaTimeSeconds)
{
	if (is_falling)
	{
		AnimateFall(deltaTimeSeconds);
		return;
	}

	// moving player to the correct position based on keyboard input
	if (move_left) // moving to the left lane
	{
		player_position -= glm::vec3(.8f, 0, 0) * deltaTimeSeconds * player_lateral_speed;
		if (player_position.x <= player_last_x - 1.05f)
		{
			move_left = false;
			player_position.x = player_last_x - 1.05f;
		}
	}
	if (move_right) // moving to the right lane
	{
		player_position += glm::vec3(.8f, 0, 0) * deltaTimeSeconds * player_lateral_speed;
		if (player_position.x >= player_last_x + 1.05f)
		{
			move_right = false;
			player_position.x = player_last_x + 1.05f;
		}
	}
	if (is_jumping)
	{
		if (player_position.y >= .5f)
		{
			float elapsed_jump = time_elapsed - jump_time;
			player_position.y += (player_jump_speed * elapsed_jump) / 4.5f
				- (player_jump_speed * ((float)(pow(elapsed_jump, 2)) / 2.2f));
		}
		else
		{
			is_jumping = false;
			player_position.y = .5f;
		}
	}
	if ((int)time_elapsed >= 4 && !move_left && !move_right && !is_jumping)
	{
		bool found = false;
		for (glm::vec3 pos : platform_positions)
		{
			if (pos.x == player_position.x && pos.z <= player_position.z + 1.f)
			{
				found = true;
				break;
			}
		}
		if (!found)
			AnimateFall(deltaTimeSeconds);
	}

	// drawing player
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, player_position);
	if (!is_affected_orange_plat && !is_falling)
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color, true);
	else if (!is_falling)	
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color, true);
}

void Tema2::PlatformPlayerInteractions(float deltaTimeSeconds)
{
	if (is_falling)
		return;

	if (is_affected_orange_plat &&
		time_elapsed >= orange_platform_start + 3)
	{
		is_affected_orange_plat = false;
		platform_speed = last_speed;
	}
	if (!is_jumping && !is_falling)
	{
		for (int i = 0; i < platform_positions.size(); ++i)
		{
			if (affects_player.at(i))
				continue;
			glm::vec3 pos = platform_positions.at(i);

			if (pos.x == player_position.x && pos.z >= player_position.z - 2)
			{
				platform_colors.at(i) = platform_color_types[5];
				if (platform_types[i] == PLATFORM_TYPE::RED)
					AnimateFall(deltaTimeSeconds);
				if (platform_types[i] == PLATFORM_TYPE::YELLOW)
					fuel_percent = max(.0f, 0.67f * fuel_percent);
				if (platform_types[i] == PLATFORM_TYPE::ORANGE &&
					!is_affected_orange_plat)
				{
					last_speed = platform_speed;
					platform_speed = MAX_PLATFORM_SPEED * 2;
					is_affected_orange_plat = true;
					orange_platform_start = time_elapsed;
				}
				if (platform_types[i] == PLATFORM_TYPE::GREEN)
					fuel_percent = min(1.f, 1.33f * fuel_percent);
				affects_player.at(i) = true;
			}
		}
	}
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader,
	const glm::mat4& model_matrix, const glm::vec3& color, bool deform)
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

	GLint defform_location = glGetUniformLocation(shader->GetProgramID(), "defform");
	GLint defform = (deform) ? 1 : 0;
	glUniform1i(defform_location, defform);

	GLint time_location = glGetUniformLocation(shader->GetProgramID(), "time");
	glUniform1f(time_location, (time_elapsed - orange_platform_start));

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::Update(float deltaTimeSeconds)
{
	time_elapsed += deltaTimeSeconds;

	// drawing user interface
	DrawUI(deltaTimeSeconds);

	// drawing platforms
	AnimatePlatforms(deltaTimeSeconds);

	// drawing player
	AnimatePlayer(deltaTimeSeconds);

	// checking collisions
	PlatformPlayerInteractions(deltaTimeSeconds);
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	if (is_falling)
		return;
	if (window->KeyHold(GLFW_KEY_A) &&
		player_position.x > -2 &&
		!(move_left || move_right))
	{
		move_left = true;
		player_last_x = player_position.x;
	}
	if (window->KeyHold(GLFW_KEY_D) &&
		player_position.x < 2 &&
		!(move_left || move_right))
	{
		move_right = true;
		player_last_x = player_position.x;
	}
	if (!is_affected_orange_plat &&
		window->KeyHold(GLFW_KEY_W) &&
		platform_speed < MAX_PLATFORM_SPEED)
	{
		platform_speed += 10 * deltaTime;
	}
	if (!is_affected_orange_plat &&
		window->KeyHold(GLFW_KEY_S) &&
		platform_speed > MIN_PLATFORM_SPEED)
	{
		platform_speed -= 10 * deltaTime;
	}
	if (window->KeyHold(GLFW_KEY_C))
	{
		is_third_person = !is_third_person;
	}
	if (window->KeyHold(GLFW_KEY_SPACE) && !is_jumping)
	{
		is_jumping = true;
		jump_time = time_elapsed;
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
