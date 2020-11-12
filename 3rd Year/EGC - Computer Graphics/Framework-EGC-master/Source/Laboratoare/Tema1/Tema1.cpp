#include "Tema1.h"

#include <Core/Engine.h>

#include <iostream>
#include <vector>

using namespace std;

Tema1::Tema1() {}

Tema1::~Tema1() {}

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

    score = 0;
    no_lives = 3;

    // init bow
    {
        bow_line_matrix = glm::mat3(1);
        Mesh *bow = new Mesh("bow");

        int m_y = resolution.y / 2;
        bow_line_pos0 = glm::vec3(100, m_y + 75, 0);
        bow_line_pos1 = glm::vec3(100, m_y - 75, 0);

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
        no_visible_balloons = 0;
        Mesh *balloon = new Mesh("balloon");

        vector<VertexFormat> vertices;
        vector<unsigned short> indices;

        vertices.emplace_back(glm::vec3(0, 0, 0), BLACK);
        for (unsigned short i = 0; i < NO_TRIANGLES; i++)
        {
            float arg = 2 * M_PI * i / NO_TRIANGLES;

            vertices.emplace_back(glm::vec3(cos(arg), sin(arg), 0), BLACK);
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
    // TODO: check for collisions between balloons and arrow
    // TODO: scale balloons down to 0 if they are hit
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        ;
    }
    // checking if any balloons are not visible anymore
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        // TODO
    }
}

// Function that spawns balloons randomly
void Tema1::SpawnBalloons()
{
    if (no_visible_balloons >= MAX_NO_BALLOONS)
        return;

    while (no_visible_balloons < MAX_NO_BALLOONS)
    {
        // choosing random position to spawn at
        glm::ivec2 resolution = window->GetResolution();
        float min_x = resolution.x / 2.f;
        float max_x = resolution.x;
        float y = resolution.y;
        float x = min_x + (rand() % (int)(max_x - min_x + 1));

        // building initial position matrix
        glm::mat3 new_pos = glm::mat3(1);
        new_pos *= glm::translate(glm::mat4(1), glm::vec3(x, y, 0));
        balloons_matrix[no_visible_balloons++] = new_pos;
    }
}

// Function that continuosly translates visible balloons upwards on screen
void Tema1::TranslateBalloons(float deltaTimeSeconds)
{
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        float factor = -deltaTimeSeconds * BALLOON_SPEED;
        balloons_matrix[i] *= glm::translate(glm::mat4(1), glm::vec3(0, factor, 0));
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
    cout << "Score: " << score << " | Lives: " << no_lives << endl;

    // drawing the bow
    // TODO: apply rotation according to mouse position
    RenderMesh2D(meshes["bow"], shaders["VertexColor"], bow_line_matrix);

    // checking if any balloons are hit
    CheckImpact();

    // spawning additional balloons, if needed
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
    // moving the bow on the OY axis
    if (window->KeyHold(GLFW_KEY_W))
    {
        // moving up (negative on axis)
        float factor = -deltaTime * BOW_MOVEMENT_SPEED;
        bow_line_matrix *= glm::translate(glm::mat4(1), glm::vec3(0, factor, 0));
    }
    else if (window->KeyHold(GLFW_KEY_S))
    {
        // moving down (positive on axis)
        float factor = deltaTime * BOW_MOVEMENT_SPEED;
        bow_line_matrix *= glm::translate(glm::mat4(1), glm::vec3(0, factor, 0));
    }
}

void Tema1::OnKeyPress(int key, int mods) {}

void Tema1::OnKeyRelease(int key, int mods) {}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // TODO: rotate bow towards mouse position
    // cout << "mouseX = " << mouseX << " mouseY = " << mouseY << endl;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // TODO: adapt arrow speed
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // TODO: release arrow
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}