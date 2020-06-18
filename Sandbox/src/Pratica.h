#pragma once

#include <SolutionShelves.h>

struct Pixel
{
	glm::vec4 Color;
};

class Pratica
{
public:
	Pratica(uint32_t width, uint32_t height, uint32_t pixelSize);
	~Pratica() = default;

	void OnUpdate(SolutionShelves::Timestep ts);
	void OnEvent(SolutionShelves::Event& event);
	void OnRender(SolutionShelves::OrthographicCameraController& cameraController);

	uint32_t ScreenWidth() const { return m_ScreenWidth; };
	uint32_t ScreenHeight() const { return m_ScreenHeight; };

	void DrawPixel(uint32_t x, uint32_t y, const glm::vec4& color);
private:
	void ClearScreen(const glm::vec4& color);
	void Noise();
private:
	std::vector<Pixel> m_ScreenBuffer;
	uint32_t m_Width, m_Height, m_PixelSize, m_ScreenBufferLenght;
	uint32_t m_ScreenWidth, m_ScreenHeight;
};
