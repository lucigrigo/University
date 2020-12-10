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
	const string texture_path = "Source/Laboratoare/Tema2/Textures/";

	// creating sphere (player)
	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// loading texture for sphere
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((texture_path + "death_star.jpg").c_str(), GL_REPEAT);
		textures["sphere_texture"] = texture;
	}

	// creating platform model
	{
		Mesh* mesh = new Mesh("platform");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// loading texture for platforms
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((texture_path + "black_white.png").c_str(), GL_REPEAT);
		textures["platform_texture"] = texture;
	}

	// loading texture for background
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((texture_path + "galaxy.jpg").c_str(), GL_REPEAT);
		textures["background"] = texture;
	}

	// loading texture for game over image
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((texture_path + "game_over.png").c_str(), GL_REPEAT);
		textures["game_over"] = texture;
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

	// initialising variables
	{
		platforms.initValues();
		player_position = glm::vec3(.0f, .5f, -3.f);
		player_color = glm::vec3(.2f, .2f, .2f);
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
		player_jump_speed = 6.f;
		rotate_factor = .0f;
		last_z = .0f;
		exit_cooldown = .0f;
	}

	// generating initial platforms
	last_z = platforms.SpawnNextPlatforms(last_z, initial_platform_positions);
}

void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(.0f, .0f, .0f, .0f);
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
	//RenderSimpleMesh(meshes["indicator"], shaders["ShaderTema2"], model_matrix, glm::vec3(.0f, .0f, .0f), false, nullptr);

	// drawing inner rectangle
	model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, glm::vec3(4, (float)1.2f - 1.25f * (1.f - fuel_percent), -3));
	model_matrix = glm::scale(model_matrix, glm::vec3(.5f, (float)2.5f * fuel_percent, .01f));
	//RenderSimpleMesh(meshes["indicator"], shaders["ShaderTema2"], model_matrix, color, false, nullptr);
}

void Tema2::AnimatePlatforms(float deltaTimeSeconds)
{
	if (is_falling)
		return;

	last_z = platforms.SpawnNextPlatforms(last_z, platform_positions, platform_colors,
		platform_types, affects_player);

	// translating and drawing visible platforms
	for (int i = 0; i < platform_positions.size(); ++i)
	{
		glm::vec3 col = platform_colors.at(i);
		glm::vec3 pos = platform_positions.at(i);

		glm::mat4 model_matrix = glm::mat4(1);
		model_matrix = glm::translate(model_matrix, pos);
		model_matrix = glm::scale(model_matrix, glm::vec3(2.f, .1f, 8.f));
		RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, col, false,
			textures["platform_texture"]);

		pos += glm::vec3(.0f, .0f, 1.f) * platform_speed * deltaTimeSeconds;
		platform_positions.at(i) = pos;
	}

	// translating initial platforms, if there are any
	if (!initial_platform_positions.empty())
	{
		for (int i = 0; i < initial_platform_positions.size(); ++i)
		{
			glm::vec3 pos = initial_platform_positions.at(i);
			glm::vec3 col = platforms.platform_color_types[0];

			glm::mat4 model_matrix = glm::mat4(1);
			model_matrix = glm::translate(model_matrix, pos);
			model_matrix = glm::scale(model_matrix, glm::vec3(2.f, .1f, 8.f));
			RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, col, false, textures["platform_texture"]);

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

			if (pos.z >= 6)
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

		if (pos.z >= 6)
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

	if (player_position.z <= -15.f) {
		if (exit_cooldown == .0f) {
			exit_cooldown = time_elapsed;
			textures["background"] = textures["game_over"];
		}
		else {
			if (time_elapsed - exit_cooldown >= 3)
				exit(0);
		}
	}
	else 
	{
		for (int i = 0; i < platform_positions.size(); ++i) {
			glm::vec3 col = platform_colors.at(i);
			glm::vec3 pos = platform_positions.at(i);
			pos += glm::vec3((rand() % 3 - 1) * 3.f, (rand() % 3 - 1) * 3.f, -8.f) * (float)MIN_PLATFORM_SPEED * deltaTimeSeconds;

			glm::mat4 model_matrix = glm::mat4(1);
			model_matrix = glm::translate(model_matrix, pos);
			model_matrix = glm::scale(model_matrix, glm::vec3(2.f, .1f, 8.f));
			RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, col, false, textures["platform_texture"]);
			platform_positions.at(i) = pos;
		}

		player_position -= glm::vec3(.0f, .4f, 1.f) * deltaTimeSeconds * (float)MIN_PLATFORM_SPEED;
		glm::mat4 model_matrix = glm::mat4(1);
		model_matrix = glm::translate(model_matrix, player_position);
		model_matrix = glm::rotate(model_matrix, -rotate_factor, glm::vec3(1.f, .0f, .0f));
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color, false, textures["sphere_texture"]);
	}
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
		if (player_position.x <= player_last_x - 2.f)
		{
			move_left = false;
			player_position.x = player_last_x - 2.f;
		}
	}

	if (move_right) // moving to the right lane
	{
		player_position += glm::vec3(.8f, 0, 0) * deltaTimeSeconds * player_lateral_speed;
		if (player_position.x >= player_last_x + 2.f)
		{
			move_right = false;
			player_position.x = player_last_x + 2.f;
		}
	}

	if (is_jumping)
	{
		if (time_elapsed - jump_time <= .3f)
			player_position.y += player_jump_speed * deltaTimeSeconds;
		else
			player_position.y -= player_jump_speed * deltaTimeSeconds;
		if (time_elapsed - jump_time >= .6f)
		{
			is_jumping = false;
			player_position.y = .5f;
		}
	}

	if (initial_platform_positions.empty() && !is_jumping)
	{
		bool found = false;
		for (glm::vec3 pos : platform_positions)
		{
			if (pos.z + 4 >= player_position.z &&
				pos.z - 4 <= player_position.z &&
				pos.x - 1 <= player_position.x &&
				pos.x + 1 >= player_position.x)
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
	model_matrix = glm::rotate(model_matrix, -rotate_factor, glm::vec3(1.f, .0f, .0f));
	if (!is_affected_orange_plat && !is_falling)
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color, false, textures["sphere_texture"]);
	else if (!is_falling)
		RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color, true, textures["sphere_texture"]);
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

			if (pos.z + 4.5f >= player_position.z &&
				pos.z - 4.5f <= player_position.z &&
				pos.x - 1.25f <= player_position.x &&
				pos.x + 1.25f >= player_position.x)
			{
				platform_colors.at(i) = platforms.platform_color_types[5];
				if (platform_types[i] == platforms.PLATFORM_TYPE::RED)
					AnimateFall(deltaTimeSeconds);
				if (platform_types[i] == platforms.PLATFORM_TYPE::YELLOW)
					fuel_percent = max(.0f, 0.67f * fuel_percent);
				if (platform_types[i] == platforms.PLATFORM_TYPE::ORANGE &&
					time_elapsed >= orange_platform_start + 1)
				{
					last_speed = platform_speed;
					platform_speed = MAX_PLATFORM_SPEED * 2;
					is_affected_orange_plat = true;
					orange_platform_start = time_elapsed;
				}
				if (platform_types[i] == platforms.PLATFORM_TYPE::GREEN)
					fuel_percent = min(1.f, 1.33f * fuel_percent);
				affects_player.at(i) = true;
			}
		}
	}
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader,
	const glm::mat4& model_matrix, const glm::vec3& color, bool is_defformed, Texture2D* texture)
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
	GLint defform = (is_defformed) ? 1 : 0;
	glUniform1i(defform_location, defform);

	GLint time_location = glGetUniformLocation(shader->GetProgramID(), "time");
	glUniform1f(time_location, time_elapsed);

	glUniform1i(glGetUniformLocation(shader->GetProgramID(), "has_texture"), (texture) ? 1 : 0);

	if (texture)
	{
		// Activate texture location 0
		glActiveTexture(GL_TEXTURE0);

		// Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

		// Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
	}

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema2::Update(float deltaTimeSeconds)
{
	time_elapsed += deltaTimeSeconds;
	rotate_factor += min((float)MAX_PLATFORM_SPEED, platform_speed) * deltaTimeSeconds * (float)0.3;
	last_z += deltaTimeSeconds * platform_speed;
	cout << 1 / deltaTimeSeconds << endl;

	// drawing user interface
	//DrawUI(deltaTimeSeconds);

	// drawing platforms
	AnimatePlatforms(deltaTimeSeconds);

	// drawing player
	AnimatePlayer(deltaTimeSeconds);

	// checking collisions
	PlatformPlayerInteractions(deltaTimeSeconds);

	// drawing background image
	glm::mat4 model_matrix = glm::mat4(1);
	model_matrix = glm::translate(model_matrix, glm::vec3(0, -15, -40));
	model_matrix = glm::scale(model_matrix, glm::vec3(120, 60, 1.f));
	RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, glm::vec3(.0f, .0f, .0f), false, textures["background"]);
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
		player_position.x > -4 &&
		!(move_left || move_right))
	{
		move_left = true;
		player_last_x = player_position.x;
	}
	if (window->KeyHold(GLFW_KEY_D) &&
		player_position.x < 4 &&
		!(move_left || move_right))
	{
		move_right = true;
		player_last_x = player_position.x;
	}
	if (!is_jumping &&
		!is_affected_orange_plat &&
		window->KeyHold(GLFW_KEY_W) &&
		platform_speed < MAX_PLATFORM_SPEED)
	{
		platform_speed += 5 * deltaTime;
	}
	if (!is_affected_orange_plat &&
		window->KeyHold(GLFW_KEY_S) &&
		platform_speed > MIN_PLATFORM_SPEED)
	{
		platform_speed -= 5 * deltaTime;
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
