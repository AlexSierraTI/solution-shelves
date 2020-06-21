#include "OldWest.h"

namespace PokerSS
{
	OldWest::OldWest()
	{
		m_LevelSize = { 3.6f, 1.97f };
		LoadAssets();
	}

	OldWest::~OldWest()
	{
	}

	void OldWest::LoadAssets()
	{
		m_LevelTexture = SolutionShelves::Texture2D::Create("assets/textures/velcro.png");
	}

	void OldWest::OnUpdate(SolutionShelves::Timestep ts)
	{

	}

	void OldWest::OnRender()
	{
		SolutionShelves::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.0f }, m_LevelSize, m_LevelTexture);
	}

	void OldWest::OnImGuiRender()
	{
		//ImGui::DragFloat2("Level Size", glm::value_ptr(m_LevelSize), 0.01f);
	}
}