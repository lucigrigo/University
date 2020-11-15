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
    arrow_matrix = glm::mat3(1);
    shuriken_matrix = glm::mat3(1);
    shuriken_shot = false;
    time_elapsed = 0.f;
    click_time = release_time = 0.f;
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

void Tema1::CreateBalloon(glm::vec3 color, string name)
{
    // drawing the circular area
    Mesh *balloon = new Mesh(name);

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
        Mesh *bow_string = new Mesh("bow_string");

        float m_y = (float)resolution.y / 2;
        glm::vec3 bow_string_pos0 = glm::vec3(0, 75, 0);
        glm::vec3 bow_string_pos1 = glm::vec3(0, -75, 0);
        bow_string_matrix = glm::mat3(1);
        bow_string_matrix *= Translate(100, m_y);

        vector<VertexFormat> vertices{VertexFormat(bow_string_pos0, BLACK),
                                      VertexFormat(bow_string_pos1, BLACK)};

        vector<unsigned short> indices = {0, 1};

        bow_string->SetDrawMode(GL_LINES);
        bow_string->InitFromData(vertices, indices);
        AddMeshToList(bow_string);

        // drawing the handle
        Mesh *bow_handle = new Mesh("bow_handle");
        vertices.clear();
        indices.clear();

        bow_handle_matrix = glm::mat3(1);
        bow_handle_matrix *= Translate(100, m_y);
        bow_handle_matrix *= Scale(20, 75);

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
        // creating meshes for the red and yellow balloons
        CreateBalloon(BALLOON_RED_COLOR, BALLOON_RED_NAME);
        CreateBalloon(BALLOON_YELLOW_COLOR, BALLOON_YELLOW_NAME);

        // drawing the string
        Mesh *balloon_string = new Mesh("balloon_string");

        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 0), BLACK),
            VertexFormat(glm::vec3(0, 1, 0), BLACK),
            VertexFormat(glm::vec3(1, 2, 0), BLACK),
            VertexFormat(glm::vec3(-1, 3, 0), BLACK),
            VertexFormat(glm::vec3(1, 4, 0), BLACK),
            VertexFormat(glm::vec3(-1, 5, 0), BLACK),
            VertexFormat(glm::vec3(0, 6, 0), BLACK),
            VertexFormat(glm::vec3(0, 7, 0), BLACK)};

        vector<unsigned short> indices = {
            0, 1,
            1, 2,
            2, 3,
            3, 4,
            4, 5,
            5, 6,
            6, 7};

        balloon_string->InitFromData(vertices, indices);
        balloon_string->SetDrawMode(GL_LINES);
        AddMeshToList(balloon_string);
    }

    // init arrow
    {
        // drawing arrow body
        Mesh *arrow = new Mesh("arrow");

        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 0), BLACK),
            VertexFormat(glm::vec3(50, 0, 0), BLACK)};

        vector<unsigned short> indices = {
            0, 1};

        arrow->InitFromData(vertices, indices);
        arrow->SetDrawMode(GL_LINES);
        AddMeshToList(arrow);

        // drawing arrow tip
        Mesh *arrow_tip = new Mesh("arrow_tip");

        vertices.clear();
        indices.clear();

        vertices = {
            VertexFormat(glm::vec3(65, 0, 0), BLACK),
            VertexFormat(glm::vec3(50, 5, 0), BLACK),
            VertexFormat(glm::vec3(50, -5, 0), BLACK)};

        indices = {
            0, 2, 1};

        arrow_tip->InitFromData(vertices, indices);
        arrow_tip->SetDrawMode(GL_TRIANGLES);
        AddMeshToList(arrow_tip);
    }

    // init shuriken
    {
        Mesh *shuriken = new Mesh("shuriken");

        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(0, 0, 0), BLACK),
            VertexFormat(glm::vec3(1, 1, 0), BLACK),
            VertexFormat(glm::vec3(2, 0, 0), BLACK),
            VertexFormat(glm::vec3(0, 2, 0), BLACK),
            VertexFormat(glm::vec3(2, 2, 0), BLACK),
            VertexFormat(glm::vec3(0, 1, 0), BLACK),
            VertexFormat(glm::vec3(1, 0, 0), BLACK),
            VertexFormat(glm::vec3(1, 2, 0), BLACK),
            VertexFormat(glm::vec3(2, 1, 0), BLACK)};

        vector<unsigned short> indices = {
            1, 4, 8,
            1, 3, 7,
            1, 0, 5,
            1, 2, 6};

        shuriken->InitFromData(vertices, indices);
        shuriken->SetDrawMode(GL_TRIANGLES);
        AddMeshToList(shuriken);
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

void Tema1::CheckBoundaries()
{
    glm::ivec2 resolution = window->GetResolution();

    // check for collisions between balloons and arrow
    // scale balloons down to 0 if they are hit
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        if (arrow_matrix[2][0] + 65 == balloons_matrix[i][2][0] &&
            arrow_matrix[2][1] >= balloons_matrix[i][2][1] - 23 &&
            arrow_matrix[2][1] <= balloons_matrix[i][2][1] + 23)
        {
            is_arrow_shot = false;
            score = (balloon_type[i] == BALLOON_RED_NAME) ? score + 2 : score - 1;
            is_hit[i] = true;
            // balloons_matrix.erase(balloons_matrix.begin() + i);
            // balloons_string_matrix.erase(balloons_string_matrix.begin() + i);
            // balloon_type.erase(balloon_type.begin() + i);
            // --no_visible_balloons;
            break;
        }
    }

    // checking for collisions between shuriken and the bow
    if (shuriken_shot && shuriken_matrix[2][0] <= bow_string_matrix[2][0])
    {
        shuriken_shot = false;
        --no_lives;
    }

    // checking for arrows that leave the screen
    if (is_arrow_shot && arrow_matrix[2][0] >= resolution.x)
        is_arrow_shot = false;

    // checking for balloons that are not visible anymore as they leave the screen
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        float curr_y = balloons_matrix[i][2][1];
        if (curr_y - 150 >= resolution.y)
        {
            balloons_matrix.erase(balloons_matrix.begin() + i);
            balloons_string_matrix.erase(balloons_string_matrix.begin() + i);
            balloon_type.erase(balloon_type.begin() + i);
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
    float min_x = (float)resolution.x / 2.f;
    float max_x = (float)resolution.x - 50;
    float y = -55.f;
    float x = min_x + (rand() % (int)(max_x - min_x + 1));

    // making sure no balloons are overlapping at spawn spot
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        if (balloons_matrix[i][2][1] <= 40 &&
            abs(balloons_matrix[i][2][0] - x) < 40)
            return;
    }

    // generating yellow balloons at a random ratio of approx. 1/5
    int r = rand() % 5;
    if (!r)
        balloon_type.push_back(BALLOON_YELLOW_NAME);
    else
        balloon_type.push_back(BALLOON_RED_NAME);

    // building initial position matrix
    glm::mat3 new_pos = glm::mat3(1);
    glm::mat3 new_string_pos = glm::mat3(1);
    new_string_pos *= Scale(5, 5);
    new_string_pos *= Translate(x / 5, y / 5 - 17);
    new_pos *= Translate(x, y);
    new_pos *= Scale(30, 55);
    balloons_matrix.push_back(new_pos);
    balloons_string_matrix.push_back(new_string_pos);
    is_hit[no_visible_balloons] = false;
    ++no_visible_balloons;
}

void Tema1::SpawnShurikens()
{
    if (shuriken_shot)
        return;

    // spawning shurikens from right side of the screen
    // coming towards the bow
    float curr_bow_x = bow_string_matrix[2][0];
    float curr_bow_y = bow_string_matrix[2][1];

    shuriken_shot = true;
    shuriken_matrix = glm::mat3(1);
    shuriken_matrix *= Translate(window->GetResolution().x, curr_bow_y);
    shuriken_matrix *= Scale(30, 30);
}

// Function that continuosly translates visible balloons upwards on screen
void Tema1::TranslateBalloons(float deltaTimeSeconds)
{
    for (int i = 0; i < no_visible_balloons; ++i)
    {
        if (is_hit[i])
            continue;
        float factor = deltaTimeSeconds * BALLOON_SPEED;
        balloons_matrix[i] *= Translate(0, factor);
        balloons_string_matrix[i] *= Translate(0, 11 * factor);
    }
}

// Function that releases arrow with given speed
void Tema1::ShootArrow(float speed)
{
    if (is_arrow_shot)
        return;
    float curr_bow_x = bow_string_matrix[2][0];
    float curr_bow_y = bow_string_matrix[2][1];
    arrow_matrix = glm::mat3(1);
    arrow_matrix *= Translate(curr_bow_x, curr_bow_y);
    arrow_speed = speed;
    is_arrow_shot = true;
}

void Tema1::Update(float deltaTimeSeconds)
{
    // setting drawing area
    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);

    // we clear the color buffer
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLineWidth(4);
    glPointSize(2);

    // updating time elapsed
    time_elapsed += deltaTimeSeconds;

    if (no_lives == 0)
    {
        cout << "Game over! Final score: " << score << endl;
        exit(0);
    }

    // displaying current score and lives remaining
    cout << "Time elapsed: " << time_elapsed << " | Score: " << score << " | Lives: " << no_lives << endl;

    // drawing the bow
    RenderMesh2D(meshes["bow_string"], shaders["VertexColor"], bow_string_matrix);
    RenderMesh2D(meshes["bow_handle"], shaders["VertexColor"], bow_handle_matrix);

    // checking if any balloons are hit
    CheckBoundaries();

    // spawning additional balloons, randomly, very few seconds
    int gen = rand() % 100;
    if (!gen)
        SpawnBalloons();

    // moving the balloons upwards
    TranslateBalloons(deltaTimeSeconds);

    // drawing visible balloons
    bool done = false;
    while (!done)
    {
        for (int i = 0; i < no_visible_balloons; ++i)
        {
            // TODO: make sure scaling effect of the hit balloon is working properly
            if (is_hit[i])
            {
                if (no_scales[i] > 30)
                {
                    balloons_matrix.erase(balloons_matrix.begin() + i);
                    balloons_string_matrix.erase(balloons_string_matrix.begin() + i);
                    balloon_type.erase(balloon_type.begin() + i);
                    --no_visible_balloons;
                    break;
                }
                balloons_matrix[i] *= Scale(.2f, .2f);
                balloons_string_matrix[i] *= Translate(0, -BALLOON_SPEED * deltaTimeSeconds * 15.f);
            }
            RenderMesh2D(meshes[balloon_type[i]], shaders["VertexColor"], balloons_matrix[i]);
            RenderMesh2D(meshes["balloon_string"], shaders["VertexColor"], balloons_string_matrix[i]);
        }
        done = true;
    }

    // translating arrow
    if (is_arrow_shot)
    {
        arrow_matrix *= Translate(arrow_speed, 0);
        RenderMesh2D(meshes["arrow"], shaders["VertexColor"], arrow_matrix);
        RenderMesh2D(meshes["arrow_tip"], shaders["VertexColor"], arrow_matrix);
    }

    // randomly spawn shurikens coming towards the player
    // translate shurikens, if there is any
    if (score >= 10)
    {
        SpawnShurikens();
        if (shuriken_shot)
        {
            // TODO: make sure rotation of the shuriken is working properly
            // shuriken_matrix *= Translate(-arrow_speed / 30.f, 0);
            shuriken_matrix[2][0] -= arrow_speed / 40.f;
            shuriken_matrix *= Rotate(10);
            RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], shuriken_matrix);
        }
    }
}

void Tema1::FrameEnd() {}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    // moving the bow on the OY axis up to the edge of the window
    if (window->KeyHold(GLFW_KEY_W) &&
        bow_string_matrix[2][1] <= window->GetResolution().y - 75)
    {
        // moving up (positive on axis)
        // TODO: rerotate bow to initial orientation
        // OR: just modify y coordinate
        float factor = deltaTime * BOW_MOVEMENT_SPEED;
        // bow_string_matrix *= Translate(0, factor);
        // bow_handle_matrix *= Translate(0, factor / 75);
        bow_string_matrix[2][1] += factor;
        bow_handle_matrix[2][1] += factor / 75;
    }
    else if (window->KeyHold(GLFW_KEY_S) &&
             bow_string_matrix[2][1] >= 0 + 75)
    {
        // moving down (negative on axis)
        // TODO: rerotate bow to initial orientation
        // OR: just modify y coordinate
        float factor = -deltaTime * BOW_MOVEMENT_SPEED;
        // bow_string_matrix *= Translate(0, factor);
        // bow_handle_matrix *= Translate(0, factor / 75);
        bow_string_matrix[2][1] -= factor;
        bow_handle_matrix[2][1] -= factor / 75;
    }
}

void Tema1::OnKeyPress(int key, int mods) {}

void Tema1::OnKeyRelease(int key, int mods) {}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // rotate bow towards mouse position
    if (mouseX >= bow_string_matrix[2][0])
    {
        float mid_x = bow_string_matrix[2][0];
        float mid_y = bow_string_matrix[2][1];
        float y_proj = mouseY - bow_string_matrix[2][1];
        float x_proj = mouseX - bow_string_matrix[2][0];
        // TODO: fix fidget spinner
        float degrees = -0.0005f * (float)atan(y_proj / x_proj);
        bow_string_matrix *= Rotate(degrees);
    }
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // charging arrow
    click_time = time_elapsed;

    // for (int i = 0; i < bow_string_matrix.length(); ++i)
    // {
    //     for (int j = 0; j < bow_string_matrix[0].length(); ++j)
    //         cout << bow_string_matrix[i][j] << " ";
    //     cout << endl;
    // }
    // float mid_x = bow_string_matrix[2][0];
    // float mid_y = bow_string_matrix[2][1];
    // float y_proj = abs(mouseY - bow_string_matrix[2][1]);
    // float x_proj = mouseX - bow_string_matrix[2][0];
    // float degrees = (float)atan(y_proj / x_proj);
    // cout << "mid_x=" << mid_x << endl;
    // cout << "mid_y=" << mid_y << endl;
    // cout << "mouseX=" << mouseX << endl;
    // cout << "mouseY=" << mouseY << endl;
    // cout << "x_proj=" << x_proj << endl;
    // cout << "y_proj=" << y_proj << endl;
    // cout << "degrees=" << degrees << endl;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // releasing arrow with variable speed
    float curr_time = time_elapsed;
    float speed = (curr_time - click_time) * 1e5; // ??????????????????????
    cout << "ARROW SPEED = " << speed << endl;
    speed = max(1.f, speed);
    speed = min(10.f, speed);
    ShootArrow(speed);
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}