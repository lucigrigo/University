#pragma once

#include <Component/SimpleScene.h>
#include <TextRenderer/TextRenderer.h>

class Laborator_BonusTextRenderer : public SimpleScene
{
	public:
		Laborator_BonusTextRenderer();
		~Laborator_BonusTextRenderer();

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

		// Draw the hud
		void drawHud();

		// The text renderer
		TextRenderer  *Text;

		// Draw primitives mode
		GLenum polygonMode;
};
