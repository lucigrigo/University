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

#define BLACK glm::vec3(0, 0, 0)
#define BALLOONS_SPAWN_WIDTH 250
#define NO_TRIANGLES 100
#define MAX_NO_BALLOONS 10
#define BALLOON_SPEED 0.5f
#define BOW_MOVEMENT_SPEED 0.8f

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

    void CheckImpact();
    void SpawnBalloons();
    void TranslateBalloons(float);
    Mesh *Tema1::CreateMesh(const char *, const std::vector<VertexFormat> &,
                            const std::vector<unsigned short> &);

protected:
    glm::vec3 bow_line_pos0, bow_line_pos1;
    glm::mat3 bow_line_matrix;
    int no_visible_balloons;
    std::vector<glm::mat3> balloons_matrix;
    unsigned short score;
    short no_lives;
};