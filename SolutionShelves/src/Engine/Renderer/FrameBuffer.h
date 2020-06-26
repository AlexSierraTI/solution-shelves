#pragma once

#include "Engine/Core/Base.h"

namespace SolutionShelves
{
	struct FrameBufferSpecification
	{
		uint32_t Width, Height;
		// FrameBufferFormar Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false;

		FrameBufferSpecification(uint32_t width, uint32_t height)
			: Width(width), Height(height)
		{

		}
	};

	class FrameBuffer
	{
	public:
		virtual ~FrameBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FrameBufferSpecification& GetSpecification() const = 0;

		static Ref<FrameBuffer> Create(const FrameBufferSpecification& spec);
	};
}

