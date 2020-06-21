#pragma once

#include "Entity.h"

namespace PokerSS
{

	class OldWest : public Entity
	{
	public:
		OldWest();
		~OldWest();

		virtual void LoadAssets() override;

		virtual void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnRender() override;

		virtual void OnImGuiRender() override;
	private:
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_LevelTexture;
		glm::vec2 m_LevelSize;
			
	};
}
