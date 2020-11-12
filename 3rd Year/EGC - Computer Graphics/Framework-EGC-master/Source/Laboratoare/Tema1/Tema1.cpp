/*
    Grigore Lucian-Florin
    Grupa 336CA
    Elemente de Grafica pe Calculator
    Tema 1 - Bow and arrow
*/
#include "Tema1.h"

using namespace std;

std::vector<glm::mat3> balloons_matrix;

Tema1::Tema1() 
{
    no_lives = 3;
    score = 0;
    no_visible_balloons = 0;
}

Tema1::~Tema1() {}

// Translate matrix
glm::mat3 Tema1::Translate(float translateX, float translateY)
{
    return glm::transpose(
        glm::mat3(1, 0, translateX,
            0, 1, translateY,
            0, 0, 1)
    );
}

// Scale matrix
glm::mat3 Tema1::Scale(float scaleX, float scaleY)
{
    return glm::transpose(
        glm::mat3(scaleX, 0, 0,
            0, scaleY, 0,
            0, 0, 1)
    );
}

// Rotate matrix
glm::mat3 Tema1::Rotate(float degrees)
{
    return glm::transpose(
        glm::mat3(cos(degrees), -sin(degrees), 0,
            sin(degrees), cos(degrees), 0,
            0, 0, 1)
    );
}

void Tema1::Init()
{
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
        // TODO: add ellipse
        Mesh *bow = new Mesh("bow");

        float m_y = resolution.y / 2;
        bow_line_pos0 = glm::vec3(0, 75, 0);
        bow_line_pos1 = glm::vec3(0, -75, 0);
        bow_line_matrix = glm::mat3(1);
        bow_line_matrix *= Translate(100, m_y);

        vector<VertexFormat> vertices{VertexFormat(bow_line_pos0, BLACK),
                                      VertexFormat(bow_line_pos1, BLACK)};

        vector<unsigned short> indices = {0, 1};

        bow->SetDrawMode(GL_LINES);
        bow->InitFromData(vertices, indices);
        AddMeshToList(bow);
    }

    // init balloon
    {
        // TODO: add coada la balon
        Mesh *balloon = new Mesh("balloon");

        vector<VertexFormat> vertices;
        vector<unsigned short> indices;

        vertices.emplace_back(glm::vec3(0, 0, 0), BALLOON_COLOR);
        for (unsigned short i = 0; i < NO_TRIANGLES; i++)
        {
            float arg = 2 * M_PI * i / NO_TRIANGLES;

            vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), BALLOON_COLOR);
            indices.push_back(i);
        }
        indices.push_back(NO_TRIANGLES);
        indices.push_back(1);

        balloon->InitFromData(vertices, indices);
        balloon->SetDrawMode(GL_TRIANGLE_FAN);
        AddMeshToList(balloon);
    }

    // TODO: init shuriken
    {
        ;
    }
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

void Tema1::CheckImpact()
{
    glm::ivec2 resolution = window->GetResolution();
    // TODO: check for collisions between balloons and arrow
    // TODO: scale balloons down to 0 if they are hit
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        ;
    }
    // checking if any balloons are not visible anymore as they leave the screen
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        int curr_y = balloons_matrix[i][2][1];
        if (curr_y - 150 >= resolution.y) {
            balloons_matrix.erase(balloons_matrix.begin() + i);
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
    float min_x = resolution.x / 2.f;
    float max_x = resolution.x - 50;
    float y = 0.f;
    float x = min_x + (rand() % (int)(max_x - min_x + 1));

    // building initial position matrix
    glm::mat3 new_pos = glm::mat3(1);
    new_pos *= Translate(x, y);
    new_pos *= Scale(30, 55);
    balloons_matrix.push_back(new_pos);
    ++no_visible_balloons;
}

// Function that continuosly translates visible balloons upwards on screen
void Tema1::TranslateBalloons(float deltaTimeSeconds)
{
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        float factor = deltaTimeSeconds * BALLOON_SPEED;
        balloons_matrix[i] *= Translate(0, factor);
    }
}

void Tema1::Update(float deltaTimeSeconds)
{
    // setting drawing area
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    // we clear the color buffer
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(5);
    glPointSize(5);

    // displaying current score and lives remaining
    // cout << "Score: " << score << " | Lives: " << no_lives << endl;

    // drawing the bow
    RenderMesh2D(meshes["bow"], shaders["VertexColor"], bow_line_matrix);

    // checking if any balloons are hit
    CheckImpact();

    // spawning additional balloons, randomly, very few seconds
    int gen = rand() % 100;
    if(!gen)
        SpawnBalloons();

    // moving the balloons upwards
    TranslateBalloons(deltaTimeSeconds);

    // drawing visible balloons
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        RenderMesh2D(meshes["balloon"], shaders["VertexColor"], balloons_matrix[i]);
    }

    // TODO: randomly spawn shurikens coming towards the player
}

void Tema1::FrameEnd() {}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // moving the bow on the OY axis up to the edge of the window
    if (window->KeyHold(GLFW_KEY_W) && bow_line_matrix[2][1] <= window->GetResolution().y - 75)
    {
        // moving up (positive on axis)
        float factor = deltaTime * BOW_MOVEMENT_SPEED;
        bow_line_matrix *= Translate(0, factor);
    }
    else if (window->KeyHold(GLFW_KEY_S) && bow_line_matrix[2][1] >= 0 + 75)
    {
        // moving down (negative on axis)
        float factor = -deltaTime * BOW_MOVEMENT_SPEED;
        bow_line_matrix *= Translate(0, factor);
    }
}

void Tema1::OnKeyPress(int key, int mods) {}

void Tema1::OnKeyRelease(int key, int mods) {}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // rotate bow towards mouse position
    if (mouseX >= bow_line_matrix[2][0]) {
        float mid_x = bow_line_matrix[2][0];
        float mid_y = bow_line_matrix[2][1];
        float y_proj = mouseY - bow_line_matrix[2][1];
        float x_proj = mouseX - bow_line_matrix[2][0];
        // TODO: fix fidget spinner
        float degrees = -0.0001f * (float) atan(y_proj / x_proj) * 180 / M_PI;
        bow_line_matrix *= Rotate(degrees);
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // TODO: charge arrow speed
    /*for (int i = 0; i < bow_line_matrix.length(); ++i) {
        for (int j = 0; j < bow_line_matrix[0].length(); ++j)
            cout << bow_line_matrix[i][j] << " ";
        cout << endl;
    }
    float mid_x = bow_line_matrix[2][0];
    float mid_y = bow_line_matrix[2][1];
    float y_proj = abs(mouseY - bow_line_matrix[2][1]);
    float x_proj = mouseX - bow_line_matrix[2][0];
    float degrees = (float)atan(y_proj / x_proj) * 180 / M_PI;
    cout << "mid_x=" << mid_x << endl;
    cout << "mid_y=" << mid_y << endl;
    cout << "mouseX=" << mouseX << endl;
    cout << "mouseY=" << mouseY << endl;
    cout << "x_proj=" << x_proj << endl;
    cout << "y_proj=" << y_proj << endl;
    cout << "degrees=" << degrees << endl;*/
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // TODO: release arrow
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}