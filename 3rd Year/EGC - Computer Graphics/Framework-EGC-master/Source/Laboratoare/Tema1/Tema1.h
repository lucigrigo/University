#pragma once
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>

#define BLACK glm::vec3(0, 0, 0)
#define BALLOONS_SPAWN_WIDTH 250
#define NO_TRIANGLES 100
#define MAX_NO_BALLOONS 10

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

	Mesh* Tema1::CreateMesh(const char* , const std::vector<VertexFormat>& , const std::vector<unsigned short>& );
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::vec3 bow_line_pos0, bow_line_pos1;
	int no_visible_balloons;
	std::vector < glm::mat3 > balloons_matrix;
};