#pragma once
#include <SolutionShelves.h>

#include <vulkan/vulkan.hpp>

namespace SolutionShelves
{
	struct PhysicalDevice
	{
		VkPhysicalDevice device = VK_NULL_HANDLE;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		VkPhysicalDeviceMemoryProperties memory_properties;
		uint32_t queue_family_index = 0;
	};

	struct Buffer
	{
		VkBuffer buffer = VK_NULL_HANDLE;
		VkDeviceMemory buffer_memory = VK_NULL_HANDLE;
		VkDeviceSize size = sizeof(unsigned int) * 64;
	};

	struct Descriptor
	{
		VkDescriptorPool descriptor_pool;
		VkDescriptorSetLayout descriptor_set_layout;
	};

	class SandboxVulkan : public Layer
	{
	public:
		SandboxVulkan();
		virtual ~SandboxVulkan() override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(SolutionShelves::Event& e) override;

	private:
		void CreateInstance(const char* app_name);
		void DestroyInstance();

		void CreateDevice();
		void DestroyDevice();

		void CreateCommandPool();
		void DestroyCommandPool();

		void ChoosePhysicalDevice();

		bool HasRequiredExtensions(const VkPhysicalDevice& physical_device, const char** required_extensions, uint32_t extension_count);
		bool GetQueueFamily(const VkPhysicalDevice& physical_device, VkQueueFlags flags, uint32_t& queue_family_index);
		uint32_t FindMemoryType(uint32_t type_filter, VkMemoryPropertyFlags properties);

		void CreateBuffer();
		void FreeBufferMemory();
		void DestroyBuffer();

		void CreateDescriptorPool();
		void DestroyDescriptorPool();
	private:
		VkInstance m_Instance = VK_NULL_HANDLE;
		VkDevice m_Device = VK_NULL_HANDLE;
		VkCommandPool m_CommandPool = VK_NULL_HANDLE;

		PhysicalDevice m_PhysicalDevice;
		Buffer m_Buffer;
		Descriptor m_Descriptor;
	};
}