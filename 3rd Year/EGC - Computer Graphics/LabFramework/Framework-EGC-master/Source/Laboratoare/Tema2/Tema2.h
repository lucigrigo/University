/*
	Grigore Lucian-Florin
	Grupa 336CA
	Elemente de Grafica pe Calculator
	Tema 2 - Skyroads
*/
#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <iostream>
#include <vector>
#include <math.h>

// including other source files
#include "Areas.h"
#include "Platforms.h"

class Tema2 : public SimpleScene
{
public:
    Tema2();
    ~Tema2();
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

    void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color, bool deform);
    void Tema2::DrawUI(float deltaTimeSeconds);
    void Tema2::AnimatePlatforms(float deltaTimeSeconds);
    void Tema2::AnimateFall(float deltaTimeSeconds);
    void Tema2::AnimatePlayer(float deltaTimeSeconds);
    void Tema2::PlatformPlayerInteractions(float deltaTimeSeconds);

protected:
    glm::vec3 player_color;
    glm::vec3 player_position;
    float player_lateral_speed;
    int no_visible_platforms;
    float platform_speed;
    std::vector<glm::vec3> platform_positions;
    std::vector<glm::vec3> platform_colors;
    std::vector<PLATFORM_TYPE> platform_types;
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
    float last_z;
};