/*
	Grigore Lucian-Florin
	Grupa 336CA
	Elemente de Grafica pe Calculator
	Tema 3 - Stylised Runner
*/
#include "Tema3.h"

using namespace std;

Tema3::Tema3()
{
    camera = new CameraTema3::CameraTema3();
}

Tema3::~Tema3()
{
    delete camera;
}

void Tema3::Init()
{
    const string texture_path = "Source/Laboratoare/Tema3/Textures/";

    // creating sphere (player)
    {
        Mesh *mesh = new Mesh("sphere");
        mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // loading mesh for cube
    {
        Mesh *mesh = new Mesh("cube");
        mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // loading texture for sphere
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D((texture_path + "death_star.jpg").c_str(), GL_REPEAT);
        textures["sphere_texture"] = texture;
    }

    // creating platform model
    {
        Mesh *mesh = new Mesh("platform");
        mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // loading texture for platforms
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D((texture_path + "bricks.jpg").c_str(), GL_REPEAT);
        textures["platform_texture"] = texture;
    }

    // loading texture for background
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D((texture_path + "earth.jpg").c_str(), GL_REPEAT);
        textures["background"] = texture;
    }

    // loading texture for game over image
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D((texture_path + "game_over.jpg").c_str(), GL_REPEAT);
        textures["game_over"] = texture;
    }

    // loading texture for fuel indicator
    {
        Texture2D *texture = new Texture2D();
        texture->Load2D((texture_path + "indicator.jpg").c_str(), GL_REPEAT);
        textures["indicator"] = texture;
    }

    // creating UI element
    {
        Mesh *mesh = new Mesh("indicator");
        mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // creating shader
    {
        Shader *shader = new Shader("ShaderTema2");
        shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
        shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // initialising camera
    {
        right = 5.f;
        left = -5.f;
        bottom = -5.f;
        top = 5.f;
        camera_position_third_person = glm::vec3(0, 2, 3.5f);

        camera->Set(camera_position_third_person, glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
        projection_matrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
    }

    // initialising variables
    {
        platforms.initValues();
        player_position = glm::vec3(.0f, .5f, -3.f);
        player_color = glm::vec3(.0f, .0f, .0f);
        no_visible_platforms = 0;
        platform_speed = MIN_PLATFORM_SPEED;
        last_acc = 0;
        time_elapsed = .0f;
        move_left = move_right = false;
        is_third_person = true;
        is_jumping = false;
        player_lateral_speed = 15.f;
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
        score = .0f;
        is_using_fuel_potion = false;
        time_remaining_fuel_potion = .0f;
        is_using_score_boost = false;
        time_remaining_score_boost = .0f;
    }

    // generating initial platforms
    last_z = platforms.SpawnNextPlatforms(last_z, initial_platform_positions);
}

void Tema3::FrameStart()
{
    // clears the color buffer (using the previously set color) and depth buffer
    glClearColor(.0f, .0f, .0f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::DrawUI(float deltaTimeSeconds)
{
    // TODO display score in top-right corner

    if (is_falling)
        return;

    // checking if we ran out of fuel
    if (fuel_percent <= .0f)
        AnimateFall(deltaTimeSeconds);

    // updating fuel level
    if ((int)time_elapsed > last_acc && time_elapsed >= 3 && !is_affected_orange_plat && !is_using_fuel_potion)
    {
        last_acc = (int)time_elapsed;
        fuel_percent -= .001f * platform_speed;
    }

    if (is_using_fuel_potion)
    {
        time_remaining_fuel_potion -= deltaTimeSeconds;

        if (time_remaining_fuel_potion <= .0f)
        {
            is_using_fuel_potion = false;
            time_remaining_fuel_potion = .0f;
        }
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
    model_matrix = glm::translate(model_matrix,
                                  glm::vec3(camera_position_third_person.x + 4, camera_position_third_person.y, -3.01));
    model_matrix = glm::scale(model_matrix, glm::vec3(.5f, 5.f, .01f));
    RenderSimpleMesh(meshes["indicator"], shaders["ShaderTema2"], model_matrix,
                     glm::vec3(1.f, 1.f, 1.f), textures["indicator"]);

    // drawing inner rectangle
    model_matrix = glm::mat4(1);
    model_matrix = glm::translate(model_matrix, glm::vec3(camera_position_third_person.x + 4,
                                                          (float)camera_position_third_person.y - 2.5f * (1 - fuel_percent), -3));
    model_matrix = glm::scale(model_matrix, glm::vec3(.5f, (float)5.f * fuel_percent, .01f));
    RenderSimpleMesh(meshes["indicator"], shaders["ShaderTema2"], model_matrix, color, textures["indicator"]);
}

void Tema3::GenerateDecorations()
{
    // generating initial decorations
    if (decorations_positions.empty())
    {
        for (float i = 0; i >= -100; i -= 10)
        {
            decorations_positions.push_back(glm::vec3(5, 0, i));
            decorations_positions.push_back(glm::vec3(-5, 0, i));
            decorations_types.push_back(SPHERE);
            decorations_types.push_back(SPHERE);
        }
    }
    else
    {
        // deleting platforms that pass the player
        for (int i = 0; i < decorations_positions.size(); ++i)
        {
            glm::vec3 pos = decorations_positions.at(i);

            if (pos.z >= 6)
            {
                decorations_positions.erase(decorations_positions.begin() + i);
                decorations_types.erase(decorations_types.begin() + i);
                break;
            }
        }

        // making sure the game does not run out of decorations
        float min_x = 0;
        for (glm::vec3 pos : decorations_positions)
        {
            if (pos.z <= min_x)
            {
                min_x = pos.z;
            }
        }

        // adding 10 new rows of platforms
        if (min_x >= -75)
        {
            for (int i = -5; i >= -55; i -= 5)
            {
                decorations_positions.push_back(glm::vec3(5, 0, min_x - i));
                decorations_positions.push_back(glm::vec3(-5, 0, min_x - i));
                decorations_types.push_back(CUBE);
                decorations_types.push_back(CUBE);
            }
        }
    }
}

void Tema3::DrawDecorations(float deltaTimeSeconds)
{
    if (is_falling)
        return;

    GenerateDecorations();

    for (int i = 0; i < decorations_positions.size(); ++i)
    {
        glm::vec3 pos = decorations_positions.at(i);
        DECORATION_TYPE type = decorations_types.at(i);

        glm::mat4 model_matrix = glm::mat4(1);
        model_matrix = glm::translate(model_matrix, pos);
        glm::vec3 col = glm::vec3(.5f, .5f, .5f);
        switch (type)
        {
        case CUBE:
            RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], model_matrix, col, false, textures["platform_texture"]);
            break;
        case SPHERE:
            RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, col, false, textures["platform_texture"]);
            break;
        default:
            break;
        }

        pos += glm::vec3(.0f, .0f, 1.f) * platform_speed * deltaTimeSeconds;
        decorations_positions.at(i) = pos;
    }
}

void Tema3::GenerateObstacles()
{
    int i = rand() % 20;
    if (i == 0 && obstacles_positions.size() < 10 && time_elapsed >= 10.f)
    {
        float x = 3 - rand() % 5;
        obstacles_positions.push_back(glm::vec3(x, 0, -80));
    }
}

bool Tema3::CheckObstacleCollision(glm::vec3 player_position, glm::vec3 obstacle_position)
{
    // TODO
    return false;
}

void Tema3::DrawObstacles(float deltaTimeSeconds)
{
    if (is_falling)
        return;

    GenerateObstacles();

    for (int i = 0; i < obstacles_positions.size(); ++i)
    {
        glm::vec3 pos = obstacles_positions.at(i);

        if (pos.z >= 6)
        {
            obstacles_positions.erase(obstacles_positions.begin() + i);
            break;
        }
    }

    for (int i = 0; i < obstacles_positions.size(); ++i)
    {
        glm::vec3 pos = obstacles_positions.at(i);

        glm::mat4 model_matrix = glm::mat4(1);
        model_matrix = glm::translate(model_matrix, pos);
        glm::vec3 col = glm::vec3(.8f, .1f, .1f);
        RenderSimpleMesh(meshes["cube"], shaders["ShaderTema2"], model_matrix, col, false, textures["platform_texture"]);

        if (CheckObstacleCollision(player_position, pos))
        {
            AnimateFall(deltaTimeSeconds);
            obstacles_positions.erase(obstacles_positions.begin() + i);
            break;
        }

        pos += glm::vec3(.0f, .0f, 1.f) * platform_speed * deltaTimeSeconds;
        obstacles_positions.at(i) = pos;
    }
}

void Tema3::GenerateCollectibles()
{
    for (int i = 0; i < collectibles_positions.size(); ++i)
    {
        glm::vec3 pos = collectibles_positions.at(i);

        if (pos.z >= 6)
        {
            collectibles_positions.erase(collectibles_positions.begin() + i);
            collectibles_types.erase(collectibles_types.begin() + i);
            break;
        }
    }

    if (collectibles_positions.empty())
    {
        for (int i = 0; i < 3; ++i)
        {
            int x = 3 - rand() % 5;
            int z = -80 - 8 * (rand() % 5);
            collectibles_positions.push_back(glm::vec3(x, .5f, z));

            x = rand() % 2;
            switch (x)
            {
            case 0:
                collectibles_types.push_back(FUEL_POTION);
                break;
            case 1:
                collectibles_types.push_back(SCORE_BOOST);
                break;
            default:
                break;
            }
        }
    }
}

bool Tema3::CheckCollectibleCollision(glm::vec3 player_position, glm::vec3 collectible_position)
{
    // TODO
    return false;
}

void Tema3::DrawCollectibles(float deltaTimeSeconds)
{
    if (time_elapsed < 10.f)
        return;

    GenerateCollectibles();

    for (int i = 0; i < collectibles_positions.size(); ++i)
    {
        glm::vec3 pos = collectibles_positions.at(i);
        COLLECTIBLE_TYPE type = collectibles_types.at(i);

        glm::mat4 model_matrix = glm::mat4(1);
        model_matrix = glm::translate(model_matrix, pos);
        glm::vec3 col;

        switch (type)
        {
        case FUEL_POTION:
            col = glm::vec3(.1f, .9f, .1f);
            break;
        case SCORE_BOOST:
            col = glm::vec3(.1f, .1f, .9f);
            break;
        default:
            col = glm::vec3(.5f, .5f, .5f);
            break;
        }

        RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, col, false, textures["platform_texture"]);

        if (CheckIntersect(pos))
        {
            switch (type)
            {
            case FUEL_POTION:
            {
                is_using_fuel_potion = true;
                time_remaining_fuel_potion = 3.f;
                break;
            }
            case SCORE_BOOST:
            {
                is_using_score_boost = true;
                time_remaining_score_boost = 3.f;
                break;
            }
            default:
                break;
            }

            collectibles_positions.erase(collectibles_positions.begin() + i);
            collectibles_types.erase(collectibles_types.begin() + i);
            break;
        }

        pos += glm::vec3(.0f, .0f, 1.f) * platform_speed * deltaTimeSeconds;
        collectibles_positions.at(i) = pos;
    }
}

bool Tema3::CheckIntersect(glm::vec3 player_position, glm::vec3 platform_position)
{
    return (platform_position.z - 4.5 <= player_position.z) &&
           (platform_position.z + 4.5 >= player_position.z) &&
           (platform_position.x - 1.5 <= player_position.x) &&
           (platform_position.x + 1.5 >= player_position.x);
}

void Tema3::AnimatePlatforms(float deltaTimeSeconds)
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

void Tema3::AnimateFall(float deltaTimeSeconds)
{
    is_falling = true;

    if (player_position.z <= -15.f)
    {
        if (exit_cooldown == .0f)
        {
            exit_cooldown = time_elapsed;
            textures["background"] = textures["game_over"];
        }
        else
        {
            if (time_elapsed - exit_cooldown >= 3)
                exit(0);
        }
    }
    else
    {
        for (int i = 0; i < platform_positions.size(); ++i)
        {
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

void Tema3::AnimatePlayer(float deltaTimeSeconds)
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
        camera->TranslateRight(player_position.x - camera_position_third_person.x);
        camera_position_third_person.x = player_position.x;
    }

    if (move_right) // moving to the right lane
    {
        player_position += glm::vec3(.8f, 0, 0) * deltaTimeSeconds * player_lateral_speed;
        if (player_position.x >= player_last_x + 2.f)
        {
            move_right = false;
            player_position.x = player_last_x + 2.f;
        }
        camera->TranslateRight(player_position.x - camera_position_third_person.x);
        camera_position_third_person.x = player_position.x;
    }

    if (is_jumping)
    {
        if (time_elapsed - jump_time <= .5f)
            player_position.y += player_jump_speed * deltaTimeSeconds;
        else
            player_position.y -= player_jump_speed * deltaTimeSeconds;
        if (time_elapsed - jump_time >= 1.f)
        {
            is_jumping = false;
            player_position.y = .5f;
        }
        camera->TranslateUpword(player_position.y - camera_position_third_person.y + 1.5f);
        camera_position_third_person.y = player_position.y + 1.5f;
    }

    if (initial_platform_positions.empty() && !is_jumping)
    {
        bool found = false;
        for (glm::vec3 pos : platform_positions)
        {
            if (CheckIntersect(player_position, pos))
            {
                found = true;
                break;
            }
        }
        if (!found)
            AnimateFall(deltaTimeSeconds);
    }

    if (!is_third_person)
        return;

    // drawing player
    glm::mat4 model_matrix = glm::mat4(1);
    model_matrix = glm::translate(model_matrix, player_position);
    model_matrix = glm::rotate(model_matrix, -rotate_factor, glm::vec3(1.f, .0f, .0f));
    if (!is_affected_orange_plat && !is_falling)
        RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color, false, textures["sphere_texture"]);
    else if (!is_falling)
        RenderSimpleMesh(meshes["sphere"], shaders["ShaderTema2"], model_matrix, player_color, true, textures["sphere_texture"]);
}

void Tema3::PlatformPlayerInteractions(float deltaTimeSeconds)
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

            if (CheckIntersect(player_position, pos))
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

void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &model_matrix,
                             const glm::vec3 &color, Texture2D *texture)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    GLint obj_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(obj_color, 1, glm::value_ptr(color));

    GLint model_location = glGetUniformLocation(shader->GetProgramID(), "Model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model_matrix));

    GLint view_location = glGetUniformLocation(shader->GetProgramID(), "View");
    glm::mat4 view_matrix = glm::lookAt(camera_position_third_person,
                                        glm::vec3(camera_position_third_person.x, camera_position_third_person.y, 0), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view_matrix));

    GLint projection_location = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glm::mat4 proj_matrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(proj_matrix));

    glUniform1i(glGetUniformLocation(shader->GetProgramID(), "defform"), 0);

    glUniform1i(glGetUniformLocation(shader->GetProgramID(), "has_texture"), (texture) ? 1 : 0);

    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

    glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);

    glBindVertexArray(mesh->GetBuffers()->VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader,
                             const glm::mat4 &model_matrix, const glm::vec3 &color, bool is_defformed, Texture2D *texture)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    glUseProgram(shader->program);

    GLint obj_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(obj_color, 1, glm::value_ptr(color));

    GLint model_location = glGetUniformLocation(shader->GetProgramID(), "Model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model_matrix));

    GLint view_location = glGetUniformLocation(shader->GetProgramID(), "View");
    glm::mat4 view_matrix = camera->GetViewMatrix();
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view_matrix));

    GLint projection_location = glGetUniformLocation(shader->GetProgramID(), "Projection");
    glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection_matrix));

    GLint defform_location = glGetUniformLocation(shader->GetProgramID(), "defform");
    GLint defform = (is_defformed) ? 1 : 0;
    glUniform1i(defform_location, defform);

    GLint time_location = glGetUniformLocation(shader->GetProgramID(), "time");
    glUniform1f(time_location, time_elapsed);

    glUniform1i(glGetUniformLocation(shader->GetProgramID(), "has_texture"), (texture) ? 1 : 0);

    if (texture)
    {
        glActiveTexture(GL_TEXTURE0);

        glBindTexture(GL_TEXTURE_2D, texture->GetTextureID());

        glUniform1i(glGetUniformLocation(shader->program, "texture"), 0);
    }

    glBindVertexArray(mesh->GetBuffers()->VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema3::Update(float deltaTimeSeconds)
{
    time_elapsed += deltaTimeSeconds;
    rotate_factor += min((float)MAX_PLATFORM_SPEED, platform_speed) * deltaTimeSeconds * (float)0.3;
    last_z += deltaTimeSeconds * platform_speed;
    if (is_using_score_boost)
    {
        score += (int)(3 * deltaTimeSeconds * platform_speed);
        time_remaining_score_boost -= deltaTimeSeconds;
        if (time_remaining_score_boost <= .0f)
        {
            is_using_score_boost = false;
            time_remaining_score_boost = .0f;
        }
    }
    else
    {
        score += (int)(deltaTimeSeconds * platform_speed);
    }
    cout << "Score: " << score << endl;

    // drawing user interface
    DrawUI(deltaTimeSeconds);

    // drawing platforms
    AnimatePlatforms(deltaTimeSeconds);

    // drawing player
    AnimatePlayer(deltaTimeSeconds);

    // TODO draw decorations

    // TODO draw obstacles

    // TODO draw collectibles

    // TODO illuminate gameplay from decorations

    // checking collisions
    PlatformPlayerInteractions(deltaTimeSeconds);

    // drawing background image
    glm::mat4 model_matrix = glm::mat4(1);
    model_matrix = glm::translate(model_matrix, glm::vec3(0, -15, -40));
    model_matrix = glm::scale(model_matrix, glm::vec3(120, 85, 1.f));
    RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix, glm::vec3(.0f, .0f, .0f), false, textures["background"]);
    /*model_matrix = glm::translate(model_matrix, camera_position_third_person + glm::vec3(0, -5, -40));
	model_matrix = glm::scale(model_matrix, glm::vec3(10, 10, 1.f));
	RenderSimpleMesh(meshes["platform"], shaders["ShaderTema2"], model_matrix,
		glm::vec3(0.f, 0.f, 0.f), textures["background"]);*/
}

void Tema3::FrameEnd()
{
    //DrawCoordinatSystem(camera->GetViewMatrix(), projection_matrix);
}

void Tema3::OnInputUpdate(float deltaTime, int mods)
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
    if (window->KeyHold(GLFW_KEY_SPACE) && !is_jumping)
    {
        is_jumping = true;
        jump_time = time_elapsed;
    }
}

void Tema3::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_C)
    {
        is_third_person = !is_third_person;
        if (is_third_person)
        {
            glm::vec3 new_camera_position = glm::vec3(camera_position_third_person.x, 1, 0);
            camera->Set(camera_position_third_person, new_camera_position, glm::vec3(0, 1, 0));
        }
        else
        {
            glm::vec3 new_camera_position = glm::vec3(player_position);
            new_camera_position.z = -10;
            camera->Set(player_position, new_camera_position, glm::vec3(0, 1, 0));
        }
    }
}

void Tema3::OnKeyRelease(int key, int mods)
{
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
