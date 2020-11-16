/*
    Grigore Lucian-Florin
    Grupa 336CA
    Elemente de Grafica pe Calculator
    Tema 1 - Bow and arrow
*/
#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <Core/Engine.h>
#include <iostream>
#include <vector>
#include <math.h>

#define BALLOON_RED_NAME "red_balloon"
#define BALLOON_YELLOW_NAME "yellow_name"
#define BALLOON_YELLOW_COLOR glm::vec3(1.f, 1.f, 0)
#define BALLOON_RED_COLOR glm::vec3(1.f, 0, 0)
#define BLACK glm::vec3(0, 0, 0)
#define NO_TRIANGLES 100
#define MAX_NO_BALLOONS 50
#define BALLOON_SPEED 5.f
#define BOW_MOVEMENT_SPEED 550.f

class Tema1 : public SimpleScene
{
public:
    Tema1();
    ~Tema1();

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

    void CheckBoundaries();
    void SpawnBalloons();
    void Tema1::SpawnShurikens();
    void TranslateBalloons(float);
    void Tema1::ShootArrow(float);
    void Tema1::CreateBalloon(glm::vec3, string);

    glm::mat3 Tema1::Translate(float, float);
    glm::mat3 Tema1::Scale(float, float);
    glm::mat3 Tema1::Rotate(float);

protected:
    glm::mat3 bow_string_matrix, bow_handle_matrix;
    int no_visible_balloons;
    std::vector<glm::mat3> balloons_matrix;
    std::vector<glm::mat3> balloons_string_matrix;
    std::vector<std::string> balloon_type;
    glm::mat3 shuriken_matrix;
    bool shuriken_shot;
    glm::mat3 arrow_matrix;
    unsigned short score;
    short no_lives;
    bool is_arrow_shot;
    float arrow_speed;
    float time_elapsed;
    float click_time, release_time;
    bool is_hit[MAX_NO_BALLOONS];
    int no_scales[MAX_NO_BALLOONS];
    float power_indicator_scale_factor;
    glm::mat3 power_indicator_matrix;
    bool is_charging_shot;
};