#pragma once

#include "PixelEngineWrapper.h"

class Fps : public PixelEngineWrapper
{
public:
	Fps(uint32_t width, uint32_t height, uint32_t pixelSize);
	virtual ~Fps() = default;

	virtual void OnUpdate(SolutionShelves::Timestep ts) override;
	virtual void OnEvent(SolutionShelves::Event& event) override;
};

