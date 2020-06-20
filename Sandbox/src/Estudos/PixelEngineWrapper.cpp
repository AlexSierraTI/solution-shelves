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
	SolutionShelves::FrameBufferSpecification fbSpec;
	fbSpec.Width = 1280;
	fbSpec.Height = 720;
	m_FrameBuffer = SolutionShelves::FrameBuffer::Create(fbSpec);
}

void PixelEngineWrapper::OnRender(SolutionShelves::OrthographicCameraController& cameraController)
{
	cameraController.SetZoomLevel(70.0f);

	SolutionShelves::Renderer2D::BeginScene(cameraController.GetCamera());
	m_FrameBuffer->Bind();

	SolutionShelves::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	SolutionShelves::RenderCommand::Clear();


	for (uint32_t y = 0; y < m_ScreenHeight; y++)
	{
		for (uint32_t x = 0; x < m_ScreenWidth; x++)
		{
			uint32_t posIndex = y * m_ScreenWidth + x;
			SolutionShelves::Renderer2D::DrawQuad({ x - m_ScreenWidth / 2.0f, m_ScreenHeight - y - m_ScreenHeight / 2.0f, 0.5f }, { 1.0f,  1.0f }, m_ScreenBuffer[posIndex].Color);
		}
	}
	m_FrameBuffer->Unbind();
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
