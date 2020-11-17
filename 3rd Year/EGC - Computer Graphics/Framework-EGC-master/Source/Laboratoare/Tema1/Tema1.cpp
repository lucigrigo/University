/*
	Grigore Lucian-Florin
	Grupa 336CA
	Elemente de Grafica pe Calculator
	Tema 1 - Bow and arrow
*/
#include "Tema1.h"

using namespace std;

Tema1::Tema1()
{
	// default initial values
	no_lives = 3;
	score = 0;
	no_visible_balloons = 0;
	is_arrow_shot = false;
	arrow_speed = 5.f;
	shuriken_matrix = glm::mat3(1);
	is_shuriken_shot = false;
	time_elapsed = 0.f;
	click_time = release_time = 0.f;
	last_second = last_display = 0;
	bow_rotation = 0;
	arrow_x = 0.f;
	shuriken_x = 0.f;
	shuriken_y = 0.f;
	shuriken_angle = 0;
	shot_time = 0;
	shot_rotation = 0;
	power_indicator_scale_factor = 1.f;
	is_shuriken_deflected = false;
	is_charging_shot = false;
	arrow_x = 0.f;
	arrow_y = 0.f;
	bow_x = 0.f;
	bow_y = 0.f;
}

Tema1::~Tema1() {}

// Translate matrix
glm::mat3 Tema1::Translate(float translateX, float translateY)
{
	return glm::transpose(
		glm::mat3(1, 0, translateX,
			0, 1, translateY,
			0, 0, 1));
}

// Scale matrix
glm::mat3 Tema1::Scale(float scaleX, float scaleY)
{
	return glm::transpose(
		glm::mat3(scaleX, 0, 0,
			0, scaleY, 0,
			0, 0, 1));
}

// Rotate matrix
glm::mat3 Tema1::Rotate(float degrees)
{
	return glm::transpose(
		glm::mat3(cos(degrees), -sin(degrees), 0,
			sin(degrees), cos(degrees), 0,
			0, 0, 1));
}

// Creates the mesh of a single type of balloon
void Tema1::CreateBalloon(glm::vec3 color, string name)
{
	// drawing the circular area
	Mesh* balloon = new Mesh(name);

	vector<VertexFormat> vertices;
	vector<unsigned short> indices;

	vertices.emplace_back(glm::vec3(0, 0, 0), color);
	for (unsigned short i = 0; i < NO_TRIANGLES; i++)
	{
		double arg = 2 * M_PI * i / NO_TRIANGLES;

		vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), color);
		indices.push_back(i);
	}
	indices.push_back(NO_TRIANGLES);
	indices.push_back(1);

	balloon->InitFromData(vertices, indices);
	balloon->SetDrawMode(GL_TRIANGLE_FAN);
	AddMeshToList(balloon);
}

void Tema1::Init()
{
	// displaying welcome message
	cout << "==========================================================" << endl;
	cout << "Game Started!" << endl << "You have 3 lives" << endl;
	cout << "Each red balloon will give you 4 points" << endl;
	cout << "Each green balloon will give you 10 points" << endl;
	cout << "Each yellow balloon will decrease your score by 2" << endl;
	cout << "Each blue balloon will restore 1 life" << endl;
	cout << "Have fun" << endl;
	cout << "==========================================================" << endl << endl;

	// setting camera position
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f,
		400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	// init bow
	{
		// drawing the string
		Mesh* bow_string = new Mesh("bow_string");

		float m_y = (float)resolution.y / 2;
		glm::vec3 bow_string_pos0 = glm::vec3(0, 75, 0);
		glm::vec3 bow_string_pos1 = glm::vec3(0, -75, 0);
		bow_x = 100;
		bow_y = m_y;

		vector<VertexFormat> vertices{ VertexFormat(bow_string_pos0, BLACK),
									  VertexFormat(bow_string_pos1, BLACK) };

		vector<unsigned short> indices = { 0, 1 };

		bow_string->SetDrawMode(GL_LINES);
		bow_string->InitFromData(vertices, indices);
		AddMeshToList(bow_string);

		// drawing the handle
		Mesh* bow_handle = new Mesh("bow_handle");
		vertices.clear();
		indices.clear();

		vertices.emplace_back(glm::vec3(0, 0, 0), BLACK);
		for (int i = 0; i <= NO_TRIANGLES / 2 + 1; i++)
		{
			double arg = 2 * M_PI * i / NO_TRIANGLES - M_PI / 2;

			vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), BLACK);
			indices.push_back(i);
		}
		indices.push_back(NO_TRIANGLES);
		indices.push_back(1);

		bow_handle->InitFromData(vertices, indices);
		bow_handle->SetDrawMode(GL_LINE_LOOP);
		AddMeshToList(bow_handle);
	}

	// init balloon
	{
		// creating meshes for the balloons
		CreateBalloon(BALLOON_RED_COLOR, BALLOON_RED_NAME);
		CreateBalloon(BALLOON_YELLOW_COLOR, BALLOON_YELLOW_NAME);
		CreateBalloon(BALLOON_GREEN_COLOR, BALLOON_GREEN_NAME);
		CreateBalloon(BALLOON_BLUE_COLOR, BALLOON_BLUE_NAME);

		// drawing the string, same for each type of balloon
		Mesh* balloon_string = new Mesh("balloon_string");

		vector<VertexFormat> vertices{
			VertexFormat(glm::vec3(0, 0, 0), BLACK),
			VertexFormat(glm::vec3(0, 1, 0), BLACK),
			VertexFormat(glm::vec3(1, 2, 0), BLACK),
			VertexFormat(glm::vec3(-1, 3, 0), BLACK),
			VertexFormat(glm::vec3(1, 4, 0), BLACK),
			VertexFormat(glm::vec3(-1, 5, 0), BLACK),
			VertexFormat(glm::vec3(0, 6, 0), BLACK),
			VertexFormat(glm::vec3(0, 7, 0), BLACK) };

		vector<unsigned short> indices = {
			0, 1,
			1, 2,
			2, 3,
			3, 4,
			4, 5,
			5, 6,
			6, 7 };

		balloon_string->InitFromData(vertices, indices);
		balloon_string->SetDrawMode(GL_LINES);
		AddMeshToList(balloon_string);
	}

	// init arrow
	{
		// drawing arrow body
		Mesh* arrow = new Mesh("arrow");

		vector<VertexFormat> vertices{
			VertexFormat(glm::vec3(0, 0, 0), BLACK),
			VertexFormat(glm::vec3(50, 0, 0), BLACK) };

		vector<unsigned short> indices = {
			0, 1 };

		arrow->InitFromData(vertices, indices);
		arrow->SetDrawMode(GL_LINES);
		AddMeshToList(arrow);

		// drawing arrow tip
		Mesh* arrow_tip = new Mesh("arrow_tip");

		vertices.clear();
		indices.clear();

		vertices = {
			VertexFormat(glm::vec3(65, 0, 0), BLACK),
			VertexFormat(glm::vec3(50, 5, 0), BLACK),
			VertexFormat(glm::vec3(50, -5, 0), BLACK) };

		indices = {
			0, 2, 1 };

		arrow_tip->InitFromData(vertices, indices);
		arrow_tip->SetDrawMode(GL_TRIANGLES);
		AddMeshToList(arrow_tip);
	}

	// init shuriken
	{
		Mesh* shuriken = new Mesh("shuriken");

		vector<VertexFormat> vertices{
			VertexFormat(glm::vec3(-1, -1, 0), BLACK),
			VertexFormat(glm::vec3(0, 0, 0), BLACK),
			VertexFormat(glm::vec3(1, -1, 0), BLACK),
			VertexFormat(glm::vec3(-1, 1, 0), BLACK),
			VertexFormat(glm::vec3(1, 1, 0), BLACK),
			VertexFormat(glm::vec3(-1, 0, 0), BLACK),
			VertexFormat(glm::vec3(0, -1, 0), BLACK),
			VertexFormat(glm::vec3(0, 1, 0), BLACK),
			VertexFormat(glm::vec3(1, 0, 0), BLACK) };

		vector<unsigned short> indices = {
			1, 4, 8,
			1, 3, 7,
			1, 0, 5,
			1, 2, 6 };

		shuriken->InitFromData(vertices, indices);
		shuriken->SetDrawMode(GL_TRIANGLES);
		AddMeshToList(shuriken);
	}

	// init power indicator
	{
		Mesh* power_indicator = new Mesh("power_indicator");
		power_indicator_matrix = glm::mat3(1);
		power_indicator_scale_factor = 1.f;

		vector<VertexFormat> vertices{
			VertexFormat(glm::vec3(0, 0, 0), BLACK),
			VertexFormat(glm::vec3(40, 0, 0), BLACK),
			VertexFormat(glm::vec3(0, 100, 0), BLACK),
			VertexFormat(glm::vec3(40, 100, 0), BLACK) };

		vector<unsigned short> indices = {
			0, 2, 3, 1, 0 };

		power_indicator->InitFromData(vertices, indices);
		power_indicator->SetDrawMode(GL_POLYGON);
		AddMeshToList(power_indicator);
	}
}

void Tema1::FrameStart()
{

}

void Tema1::CheckBoundaries()
{
	glm::ivec2 resolution = window->GetResolution();

	// checking for collisions between arrow and the shuriken
	if (is_arrow_shot &&
		is_shuriken_shot &&
		arrow_x + cos(shot_rotation) * 65 >= shuriken_x - 20 &&
		arrow_x + cos(shot_rotation) * 65 <= shuriken_x + 20 &&
		arrow_y + sin(shot_rotation) * 65 <= shuriken_y + 20 &&
		arrow_y + sin(shot_rotation) * 65 >= shuriken_y - 20) {
		is_shuriken_shot = false;
		is_shuriken_deflected = true;
		shuriken_angle = 45 - shot_rotation;
	}

	// checking for collisions between balloons and arrow
	if (is_arrow_shot) {
		for (int i = 0; i < no_visible_balloons; ++i)
		{
			if (!is_hit[i] &&
				arrow_x + cos(shot_rotation) * 65 >= balloon_x[i] - 30 &&
				arrow_x + cos(shot_rotation) * 65 <= balloon_x[i] + 30 &&
				arrow_y + sin(shot_rotation) * 65 >= balloon_y[i] - 55 &&
				arrow_y + sin(shot_rotation) * 65 <= balloon_y[i] + 55)
			{
				if (balloon_type[i] == BALLOON_RED_NAME)
					score += 4;
				else if (balloon_type[i] == BALLOON_GREEN_NAME)
					score += 10;
				else if (balloon_type[i] == BALLOON_YELLOW_NAME)
					score = max(score, 0);
				else
					no_lives = min(3, no_lives + 1);
				is_hit[i] = true;
				break;
			}
		}
	}

	// checking for collisions between shuriken and the bow
	if (is_shuriken_shot &&
		shuriken_x <= bow_x &&
		shuriken_y <= bow_y + 75 &&
		shuriken_y >= bow_y - 75)
	{
		is_shuriken_shot = false;
		--no_lives;
	}

	// checking to see if the shuriken leaves screen area
	if ((is_shuriken_shot ||
		is_shuriken_deflected) &&
		(shuriken_x <= 0 ||
			shuriken_x >= resolution.x ||
			shuriken_y >= resolution.y ||
			shuriken_y <= 0)) {
		is_shuriken_shot = false;
		is_shuriken_deflected = false;
	}

	// checking for arrows that leave the screen
	if (is_arrow_shot &&
		(arrow_x + cos(shot_rotation) >= resolution.x ||
			arrow_y + sin(shot_rotation) <= 0 ||
			arrow_y + sin(shot_rotation) >= resolution.y))
		is_arrow_shot = false;

	// checking for balloons that are not visible anymore as they leave the screen
	for (int i = 0; i < no_visible_balloons; ++i)
	{
		if (is_hit[i])
			continue;
		float curr_y = balloon_y[i];
		if (curr_y - 150 >= resolution.y)
		{
			balloon_type.erase(balloon_type.begin() + i);
			no_scales.erase(no_scales.begin() + i);
			is_hit.erase(is_hit.begin() + i);
			balloon_x.erase(balloon_x.begin() + i);
			balloon_y.erase(balloon_y.begin() + i);
			--no_visible_balloons;
			break;
		}
	}
}

// Function that spawns balloons randomly
void Tema1::SpawnBalloons()
{
	if (no_visible_balloons >= MAX_NO_BALLOONS)
		return;

	// choosing random position to spawn at
	glm::ivec2 resolution = window->GetResolution();
	float min_x = (float)resolution.x / 3.f;
	float max_x = (float)resolution.x - 50;
	float y = -55.f;
	float x = min_x + (rand() % (int)(max_x - min_x + 1));

	// making sure no balloons are overlapping at spawn spot
	for (int i = 0; i < no_visible_balloons; ++i)
	{
		if (balloon_y[i] <= 40 &&
			abs(balloon_x[i] - x) < 40)
			return;
	}

	// generating new balloons
	int r = rand() % 100;
	if (r == 69)
		balloon_type.push_back(BALLOON_BLUE_NAME);
	else {
		if (!r)
			balloon_type.push_back(BALLOON_GREEN_NAME);
		else {
			r = rand() % 5;
			if (!r)
				balloon_type.push_back(BALLOON_YELLOW_NAME);
			else
				balloon_type.push_back(BALLOON_RED_NAME);
		}
	}

	// setting initial values
	is_hit.push_back(false);
	no_scales.push_back(0);
	balloon_x.push_back(x);
	balloon_y.push_back(y);
	++no_visible_balloons;
}

void Tema1::SpawnShurikens()
{
	if (is_shuriken_shot || is_shuriken_deflected)
		return;

	int safe_factor = rand() % 1000;
	if (!safe_factor)
		return;

	// spawning shurikens from right side of the screen
	// coming towards the bow
	float curr_bow_x = bow_x;
	float curr_bow_y = bow_y;

	is_shuriken_deflected = false;
	is_shuriken_shot = true;
	shuriken_x = (float)window->GetResolution().x;
	shuriken_y = curr_bow_y;
}

// Function that releases arrow with given speed
void Tema1::ShootArrow(float speed)
{
	if (is_arrow_shot)
		return;

	arrow_speed = speed;
	arrow_x = bow_x;
	arrow_y = bow_y;
	is_arrow_shot = true;
}

void Tema1::Update(float deltaTimeSeconds)
{
	// setting drawing area
	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);

	// we clear the color buffer
	glClearColor(0.8f, 0.8f, 0.8f, 0.8f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLineWidth(4);
	glPointSize(2);

	// updating time elapsed
	time_elapsed += deltaTimeSeconds;

	// to prevent overpowered shots right when cooldowns ends
	if (!is_arrow_shot &&
		!is_charging_shot)
		click_time = time_elapsed;

	// displayin end-game message
	if (no_lives == 0)
	{
		cout << "==========================================================" << endl;
		cout << "Game over! Final score: " << score << endl;
		cout << "==========================================================" << endl;
		exit(0);
	}

	// resetting shot cooldown
	if (!is_charging_shot &&
		is_arrow_shot &&
		(int)time_elapsed - (int)shot_time == 3)
		is_arrow_shot = false;

	// displaying current score and lives remaining
	last_second = (int)time_elapsed;
	if (last_second == last_display + 5) {
		last_display = last_second;
		cout << "Time elapsed: " << last_display << " | Score: " << score << " | Lives: " << no_lives << endl;
	}

	// drawing the bow 
	{
		glm::mat3 model_matrix = glm::mat3(1);
		model_matrix *= Translate(bow_x, bow_y);
		model_matrix *= Rotate(bow_rotation);
		RenderMesh2D(meshes["bow_string"], shaders["VertexColor"], model_matrix);

		model_matrix = glm::mat3(1);
		model_matrix *= Translate(bow_x, bow_y);
		model_matrix *= Rotate(bow_rotation);
		model_matrix *= Scale(35, 75);
		RenderMesh2D(meshes["bow_handle"], shaders["VertexColor"], model_matrix);
	}

	// checking for any type of conflict
	CheckBoundaries();

	// spawning additional balloons, randomly
	int gen = rand() % 100;
	if (!gen)
		SpawnBalloons();

	// drawing visible balloons
	bool done = false;
	while (!done) {
		done = true;
		for (int i = 0; i < no_visible_balloons; ++i)
		{
			float curr_x = balloon_x[i];
			float curr_y = balloon_y[i];

			// drawing non-hit balloons and translating them upwards
			if (!is_hit[i]) {
				glm::mat3 model_matrix = glm::mat3(1);
				model_matrix *= Translate(curr_x, curr_y);
				model_matrix *= Scale(30, 55);
				RenderMesh2D(meshes[balloon_type[i]], shaders["VertexColor"], model_matrix);

				model_matrix = glm::mat3(1);
				model_matrix *= Translate(curr_x, curr_y - 80);
				model_matrix *= Scale(5, 5);
				RenderMesh2D(meshes["balloon_string"], shaders["VertexColor"], model_matrix);

				balloon_y[i] += deltaTimeSeconds * BALLOON_SPEED;
			}
			// drawing hit balloons getting scaled to 0 and their string falling
			else {
				++no_scales[i];
				float ratio = (float)1 / no_scales[i];

				glm::mat3 model_matrix = glm::mat3(1);
				model_matrix *= Translate(curr_x, curr_y);
				model_matrix *= Scale(ratio, ratio);
				model_matrix *= Scale(30, 55);
				RenderMesh2D(meshes[balloon_type[i]], shaders["VertexColor"], model_matrix);

				model_matrix = glm::mat3(1);
				model_matrix *= Translate(0, -no_scales[i] * BALLOON_SPEED / 80);
				model_matrix *= Translate(curr_x, curr_y);
				model_matrix *= Scale(5, 5);
				RenderMesh2D(meshes["balloon_string"], shaders["VertexColor"], model_matrix);

				if (no_scales[i] > 200) {
					balloon_type.erase(balloon_type.begin() + i);
					is_hit.erase(is_hit.begin() + i);
					no_scales.erase(no_scales.begin() + i);
					balloon_x.erase(balloon_x.begin() + i);
					balloon_y.erase(balloon_y.begin() + i);
					--no_visible_balloons;
					done = false;
					break;
				}
			}
		}
	}

	// drawing arrow when getting shot
	if (is_arrow_shot)
	{
		float x_translate = abs(deltaTimeSeconds * cos(shot_rotation) * arrow_speed * 100);
		float y_translate = deltaTimeSeconds * sin(shot_rotation) * arrow_speed * 100;
		glm::mat3 model_matrix = glm::mat3(1);
		model_matrix *= Translate(arrow_x + x_translate, arrow_y + y_translate);
		model_matrix *= Rotate(shot_rotation);
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], model_matrix);
		RenderMesh2D(meshes["arrow_tip"], shaders["VertexColor"], model_matrix);
		arrow_x += x_translate;
		arrow_y += y_translate;
	}

	// randomly spawn shurikens coming towards the player
	if (score >= 20)
	{
		SpawnShurikens();

		// if shuriken is coming towards the player
		if (is_shuriken_shot)
		{
			shuriken_matrix = glm::mat3(1);
			shuriken_x -= deltaTimeSeconds * 700;
			shuriken_matrix *= Translate(shuriken_x, shuriken_y);
			shuriken_matrix *= Scale(20, 20);
			shuriken_matrix *= Rotate(time_elapsed * 10);

			RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], shuriken_matrix);
		}
		// if shuriken was deflected by an arrow
		else if (is_shuriken_deflected) {
			shuriken_matrix = glm::mat3(1);
			shuriken_x += deltaTimeSeconds * 700 * cos(shuriken_angle);
			shuriken_y += deltaTimeSeconds * 700 * sin(shuriken_angle);
			shuriken_matrix *= Translate(shuriken_x, shuriken_y);
			shuriken_matrix *= Scale(20, 20);
			shuriken_matrix *= Rotate(time_elapsed * 10);

			RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], shuriken_matrix);
		}
	}

	// scaling power indicator when charging a shot
	if (is_charging_shot &&
		power_indicator_scale_factor < (window->GetResolution().y / 100))
	{
		power_indicator_scale_factor += deltaTimeSeconds * 0.01f;
		power_indicator_matrix *= Scale(1.f, power_indicator_scale_factor);
	}

	// drawwing the arrow and power indicator when not charging a shot
	if (!is_arrow_shot) {
		RenderMesh2D(meshes["power_indicator"], shaders["VertexColor"], power_indicator_matrix);
		glm::mat3 model_matrix = glm::mat3(1);
		float curr_bow_x = bow_x;
		float curr_bow_y = bow_y;
		model_matrix *= Translate(curr_bow_x, curr_bow_y);
		model_matrix *= Rotate(bow_rotation);
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], model_matrix);
		RenderMesh2D(meshes["arrow_tip"], shaders["VertexColor"], model_matrix);
	}
}

void Tema1::FrameEnd() {}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	float factor = deltaTime * BOW_MOVEMENT_SPEED;

	// moving the bow on the OY axis up to the edge of the window
	if (window->KeyHold(GLFW_KEY_W) && bow_y <= window->GetResolution().y - 75)
	{
		// moving up (positive on axis)
		bow_y += factor;
	}
	else if (window->KeyHold(GLFW_KEY_S) && bow_y >= 0 + 75)
	{
		// moving down (negative on axis)
		bow_y -= factor;
	}
}

void Tema1::OnKeyPress(int key, int mods) {}

void Tema1::OnKeyRelease(int key, int mods) {}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// rotate bow towards mouse position
	if (mouseX >= bow_x)
	{
		float rez_y = (float)window->GetResolution().y;
		float y_proj = (rez_y - mouseY) - bow_y;
		float x_proj = mouseX - bow_x;
		float degrees = (float)atan(y_proj / x_proj);
		int m_y = window->GetResolution().y / 2;

		bow_rotation = degrees;
	}
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	if (is_arrow_shot)
		return;

	// charging arrow
	click_time = time_elapsed;
	is_charging_shot = true;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	if (is_arrow_shot)
		return;

	// releasing arrow with variable speed
	shot_time = time_elapsed;
	shot_rotation = bow_rotation;
	is_charging_shot = false;
	power_indicator_scale_factor = 1.f;
	power_indicator_matrix = glm::mat3(1);
	float speed = (time_elapsed - click_time) * 15.f;
	speed = max(6.f, speed);
	speed = min(20.f, speed);
	ShootArrow(speed);
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}