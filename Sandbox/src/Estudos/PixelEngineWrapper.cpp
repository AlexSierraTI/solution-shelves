#include "PixelEngineWrapper.h"

PixelEngineWrapper::PixelEngineWrapper(uint32_t width, uint32_t height, uint32_t pixelSize)
	: m_Width(width), 
	m_Height(height), 
	m_PixelSize(pixelSize),
	m_ScreenBufferLenght((m_Width / m_PixelSize) * (m_Height / m_PixelSize)),
	m_ScreenWidth(m_Width / m_PixelSize),
	m_ScreenHeight(m_Height / m_PixelSize)

{
	m_ScreenBuffer.resize(m_ScreenBufferLenght);
	ClearScreen({ 0.3f, 0.3f, 0.3f, 1.0f });
}

void PixelEngineWrapper::OnRender(SolutionShelves::OrthographicCameraController& cameraController)
{
	SolutionShelves::Renderer2D::BeginScene(cameraController.GetCamera());

	auto bounds = cameraController.GetBounds();
	const float boundSize = 2.0f;
	const float boundHalfSize = 1.0f;

	auto windowWidth = SolutionShelves::Application::Get().GetWindow().GetWidth();
	auto windowHeight = SolutionShelves::Application::Get().GetWindow().GetHeight();
	auto pos = cameraController.GetCamera().GetPosition();

	float pixelPosStartX = ((float)windowWidth - m_Width) / 2;
	float pixelPosStartY = ((float)windowHeight - m_Height) / 2;
	float normalPosStartX = (pixelPosStartX / windowWidth) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;    // | SEGREDO DE TUDO
	// float normalPosStartX = (pixelPosStartX / windowWidth) * boundSize - boundHalfSize;
	float normalPosStartY = bounds.GetHeight() * 0.5f - (pixelPosStartY / windowHeight) * bounds.GetHeight(); // | SEGREDO DE TUDO
	// float normalPosStartY = boundHalfSize - (pixelPosStartY / windowHeight) * boundSize;
	float normalPixelSizeX = ((-normalPosStartX) * 2) / (float)m_ScreenWidth;
	float normalPixelSizeY = ((-normalPosStartY) * 2) / (float)m_ScreenHeight;

	glm::vec2 size = { normalPixelSizeX, normalPixelSizeY };

	for (uint32_t y = 0; y < m_ScreenHeight; y++)
	{
		for (uint32_t x = 0; x < m_ScreenWidth; x++)
		{
			uint32_t posIndex = y * m_ScreenWidth + x;
			float xNormal = normalPosStartX + (x * normalPixelSizeX);
			float yNormal = normalPosStartY + (y * normalPixelSizeY);
			glm::vec3 position = { xNormal + pos.x, yNormal + pos.y, 0.0f };
			SolutionShelves::Renderer2D::DrawQuad(position, size, m_ScreenBuffer[posIndex].Color);
		}
	}
	SolutionShelves::Renderer2D::EndScene();
}

void PixelEngineWrapper::DrawPixel(uint32_t x, uint32_t y, const glm::vec4& color)
{
	uint32_t posIndex = y * m_ScreenWidth + x;
	Pixel& pixel = m_ScreenBuffer[posIndex];
	pixel.Color = color;
}

void PixelEngineWrapper::ClearScreen(const glm::vec4& color)
{
	for (uint32_t y = 0; y < m_ScreenHeight; y++)
	{
		for (uint32_t x = 0; x < m_ScreenWidth; x++)
		{
			uint32_t posIndex = y * m_ScreenWidth + x;
			Pixel& pixel = m_ScreenBuffer[posIndex];
			pixel.Color = color;
		}
	}
}
