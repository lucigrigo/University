/*
	Grigore Lucian-Florin
	Grupa 336CA
	Elemente de Grafica pe Calculator
	Tema 3 - Stylised Runner
*/
#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "T3_Platforms.h"
#include "Tema3Levels.h"
#include "LabCamera.h"
#include <TextRenderer/TextRenderer.h>
#include <string>

const enum DECORATION_TYPE {
    PYRAMID,
    SPHERE,
    CUBE
};

const enum COLLECTIBLE_TYPE {
    FUEL_POTION,
    SCORE_BOOST
};

typedef struct {
    std::string* msg;
    float time_remaining;
    float x;
    float y;
} Message;

class Tema3 : public SimpleScene
{
public:
    Tema3();
    ~Tema3();
    void Init() override;

private:
    void FrameStart() override;
    void Update(float deltaTimeSeconds) override;
    void FrameEnd() override;
    void OnInputUpdate(float deltaTime, int mods) override;
    void OnKeyPress(int key, int mods) override;
    void OnKeyRelease(int key, int mods) override;
    void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
    void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
    void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
    void OnWindowResize(int width, int height) override;

    /* TEMA 2 FUNCTII */
    void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &model_matrix,
                                 const glm::vec3 &color, Texture2D *texture);
    void Tema3::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix,
                                 const glm::vec3 &color, bool deform, Texture2D *texture);
    void Tema3::DrawUI(float deltaTimeSeconds);
    bool Tema3::CheckIntersect(glm::vec3 player_position, glm::vec3 platform_position);
    void Tema3::AnimatePlatforms(float deltaTimeSeconds);
    void Tema3::AnimateFall(float deltaTimeSeconds);
    void Tema3::AnimatePlayer(float deltaTimeSeconds);
    void Tema3::PlatformPlayerInteractions(float deltaTimeSeconds);

    /* TEMA 3 FUNCTII */
    void Tema3::GenerateDecorations();
    void Tema3::DrawDecorations(float deltaTimeSeconds);
    void Tema3::GenerateObstacles();
    void Tema3::DrawObstacles(float deltaTimeSeconds);
    void Tema3::GenerateCollectibles();
    void Tema3::DrawCollectibles(float deltaTimeSeconds);
    bool Tema3::CheckObstacleCollision(glm::vec3 player_position, glm::vec3 obstacle_position);
    bool Tema3::CheckCollectibleCollision(glm::vec3 player_position, glm::vec3 collectible_position);
    void Tema3::DisplayScore(float deltaTimeSeconds);

protected:
    /* TEMA 2 VARIABILE */
    glm::vec3 player_color;
    glm::vec3 player_position;
    float player_lateral_speed;
    int no_visible_platforms;
    float platform_speed;
    std::vector<glm::vec3> platform_positions;
    std::vector<glm::vec3> platform_colors;
    std::vector<T3_Platforms::PLATFORM_TYPE> platform_types;
    std::vector<glm::vec3> initial_platform_positions;
    std::vector<bool> affects_player;
    int last_acc;
    float time_elapsed;
    bool move_left;
    bool move_right;
    bool is_third_person;
    bool is_jumping;
    float player_last_x;
    float fuel_percent;
    int orange_platform_start;
    int is_affected_orange_plat;
    float last_speed;
    bool is_falling;
    float jump_time;
    float player_jump_speed;
    std::unordered_map<std::string, Texture2D *> textures;
    float rotate_factor;
    float last_z;
    T3_Platforms platforms;
    float exit_cooldown;
    CameraTema3::CameraTema3 *camera;
    glm::mat4 projection_matrix;
    float right, left, top, bottom;
    glm::vec3 camera_position_third_person;
    float const Z_NEAR = 1.f;
    float const Z_FAR = 50.f;
    float score;

    /* TEMA 3 VARIABILE */
    std::vector<glm::vec3> decorations_positions;
    std::vector<DECORATION_TYPE> decorations_types;
    std::vector<glm::vec3> collectibles_positions;
    std::vector<COLLECTIBLE_TYPE> collectibles_types;
    std::vector<glm::vec3> obstacles_positions;
    bool is_using_fuel_potion;
    float time_remaining_fuel_potion;
    bool is_using_score_boost;
    float time_remaining_score_boost;
    TextRenderer* Text;
    std::vector<Message> messages;
    float last_msg;
};