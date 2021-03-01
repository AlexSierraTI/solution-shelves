#include "SandboxVulkan.h"

namespace SolutionShelves
{

	SandboxVulkan::SandboxVulkan()
	{
		CreateInstance("Sandbox");
		ChoosePhysicalDevice();
		CreateDevice();
		CreateCommandPool();
		CreateBuffer();
		CreateDescriptorPool();
	}

	SandboxVulkan::~SandboxVulkan()
	{
		DestroyDescriptorPool();
		DestroyBuffer();
		DestroyCommandPool();
		DestroyDevice();
		DestroyInstance();
	}

	void SandboxVulkan::OnAttach()
	{
	}

	void SandboxVulkan::OnDetach()
	{
	}

	void SandboxVulkan::OnUpdate(SolutionShelves::Timestep ts)
	{
	}

	void SandboxVulkan::OnImGuiRender()
	{
	}

	void SandboxVulkan::OnEvent(SolutionShelves::Event& e)
	{
	}
	void SandboxVulkan::CreateInstance(const char * app_name)
	{
		const uint32_t layer_count = 1;
		const char* instance_layer[layer_count] = { "VK_LAYER_LUNARG_standard_validation" };
		const uint32_t extension_count = 1;
		const char* instace_extensions[extension_count] = { "VK_EXT_debug_report" };

		VkApplicationInfo app_info = {};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = app_name;
		app_info.pEngineName = "Solution Shelves";
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.apiVersion = VK_MAKE_VERSION(1, 2, 162);

		VkInstanceCreateInfo create_info = { };
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;
		create_info.enabledExtensionCount = 1;
		create_info.ppEnabledExtensionNames = instace_extensions;
		create_info.enabledLayerCount = 1;
		create_info.ppEnabledLayerNames = instance_layer;

		VkResult result = vkCreateInstance(
			&create_info,
			NULL,
			&m_Instance
		);

		SS_ASSERT(result == VK_SUCCESS);
	}
	void SandboxVulkan::DestroyInstance()
	{
		vkDestroyInstance(
			m_Instance,
			NULL
		);
	}

	void SandboxVulkan::CreateDevice()
	{
		const uint32_t extension_count = 1;
		const char* device_extensions[extension_count] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		static const float queue_priority = 1.0f;
		VkDeviceQueueCreateInfo queue_create_info = {};
		queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info.queueFamilyIndex = m_PhysicalDevice.queue_family_index;
		queue_create_info.queueCount = 1;
		queue_create_info.pQueuePriorities = &queue_priority;

		VkDeviceCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		create_info.pQueueCreateInfos = &queue_create_info;
		create_info.queueCreateInfoCount = 1;
		create_info.pEnabledFeatures = &m_PhysicalDevice.features;
		create_info.enabledExtensionCount = extension_count;
		create_info.ppEnabledExtensionNames = device_extensions;

		VkResult result = vkCreateDevice(
			m_PhysicalDevice.device,
			&create_info,
			nullptr,
			&m_Device
		);

		SS_ASSERT(result == VK_SUCCESS);
	}

	void SandboxVulkan::DestroyDevice()
	{
		vkDestroyDevice(
			m_Device,
			nullptr
		);
	}

	void SandboxVulkan::CreateCommandPool()
	{
		VkCommandPoolCreateInfo pool_info = {};
		pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pool_info.queueFamilyIndex = m_PhysicalDevice.queue_family_index;
		pool_info.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

		VkResult result = vkCreateCommandPool(
			m_Device,
			&pool_info,
			nullptr,
			&m_CommandPool
		);

		SS_ASSERT(result == VK_SUCCESS);
	}

	void SandboxVulkan::DestroyCommandPool()
	{
		vkDestroyCommandPool(
			m_Device,
			m_CommandPool,
			nullptr
		);
	}

	void SandboxVulkan::ChoosePhysicalDevice()
	{

		uint32_t device_count = 0;
		vkEnumeratePhysicalDevices(
			m_Instance,
			&device_count,
			nullptr
		);

		VkPhysicalDevice* devices = new VkPhysicalDevice[device_count];
		vkEnumeratePhysicalDevices(
			m_Instance,
			&device_count,
			devices
		);

		const uint32_t extension_count = 1;
		const char* device_extensions[extension_count] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

		for (uint32_t i = 0; i < device_count; i++)
		{
			if (HasRequiredExtensions(devices[i], device_extensions, extension_count))
			{
				uint32_t queue_family_index = 0;
				if (GetQueueFamily(devices[i], VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT, queue_family_index))
				{
					VkPhysicalDeviceProperties physical_device_properties;
					vkGetPhysicalDeviceProperties(
						devices[i],
						&physical_device_properties
					);

					VkPhysicalDeviceFeatures physical_device_features;
					vkGetPhysicalDeviceFeatures(
						devices[i],
						&physical_device_features
					);

					VkPhysicalDeviceMemoryProperties physical_device_mem_properties;
					vkGetPhysicalDeviceMemoryProperties(
						devices[i],
						&physical_device_mem_properties
					);


					if (m_PhysicalDevice.device == VK_NULL_HANDLE || physical_device_properties.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
					{
						m_PhysicalDevice.device = devices[i];
						m_PhysicalDevice.properties = physical_device_properties;
						m_PhysicalDevice.features = physical_device_features;
						m_PhysicalDevice.memory_properties = physical_device_mem_properties;
						m_PhysicalDevice.queue_family_index = queue_family_index;
					}
				}
			}
		}

		SS_ASSERT(m_PhysicalDevice.device != VK_NULL_HANDLE);
	}

	bool SandboxVulkan::HasRequiredExtensions(const VkPhysicalDevice& physical_device, const char** required_extensions, uint32_t extension_count)
	{
		uint32_t device_extension_count = 0;
		vkEnumerateDeviceExtensionProperties(
			physical_device,
			nullptr,
			&device_extension_count,
			nullptr
		);

		VkExtensionProperties* extensions = new VkExtensionProperties[device_extension_count];
		vkEnumerateDeviceExtensionProperties(
			physical_device,
			nullptr,
			&device_extension_count,
			extensions
		);

		for (uint32_t i = 0; i < extension_count; i++)
		{
			bool extension_found = false;
			for (uint32_t j = 0; i < device_extension_count; j++)
			{
				if (strcmp(required_extensions[i], extensions[j].extensionName) == 0)
				{
					extension_found = true;
					break;
				}
			}

			if (!extension_found)
			{
				delete[] extensions;
				return false;
			}
		}

		delete[] extensions;
		return true;
	}
	bool SandboxVulkan::GetQueueFamily(const VkPhysicalDevice& physical_device, VkQueueFlags flags, uint32_t& queue_family_index)
	{
		uint32_t queue_family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(
			physical_device,
			&queue_family_count,
			nullptr
		);

		VkQueueFamilyProperties* queue_families = new VkQueueFamilyProperties[queue_family_count];
		vkGetPhysicalDeviceQueueFamilyProperties(
			physical_device,
			&queue_family_count,
			queue_families
		);

		for (uint32_t i = 0; i < queue_family_count; i++)
		{
			if (queue_families[i].queueCount > 0)
			{
				if ((queue_families[i].queueFlags & flags) == flags)
				{
					queue_family_index = i;
					delete[] queue_families;
					return true;
				}
			}
		}

		delete[] queue_families;
		return false;
	}
	
	uint32_t SandboxVulkan::FindMemoryType(uint32_t type_filter, VkMemoryPropertyFlags properties)
	{
		for (uint32_t i = 0; i < m_PhysicalDevice.memory_properties.memoryTypeCount; i++)
		{
			if (type_filter & (1 << i) && (m_PhysicalDevice.memory_properties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}
		return -1;
	}

	void SandboxVulkan::CreateBuffer()
	{
		unsigned int example_input_data[64];
		for (unsigned int i = 0; i < 64; i++)
		{
			example_input_data[i] = i;
		}

		VkMemoryPropertyFlags buffer_memory_properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

		VkBufferCreateInfo buffer_info = {};
		buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		buffer_info.size = m_Buffer.size;
		buffer_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VkResult result = vkCreateBuffer(
			m_Device,
			&buffer_info,
			nullptr,
			&m_Buffer.buffer
		);

		SS_ASSERT(result == VK_SUCCESS);

		VkMemoryRequirements memory_requirements;
		vkGetBufferMemoryRequirements(
			m_Device,
			m_Buffer.buffer,
			&memory_requirements
		);

		uint32_t memory_type = FindMemoryType(
			memory_requirements.memoryTypeBits,
			buffer_memory_properties
		);

		VkMemoryAllocateInfo memory_allocate_info = {};
		memory_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		memory_allocate_info.allocationSize = m_Buffer.size;
		memory_allocate_info.memoryTypeIndex = memory_type;

		VkResult memory_allocation_result = vkAllocateMemory(
			m_Device,
			&memory_allocate_info,
			nullptr,
			&m_Buffer.buffer_memory
		);

		SS_ASSERT(memory_allocation_result == VK_SUCCESS);

		VkResult buffer_bind_result = vkBindBufferMemory(
			m_Device,
			m_Buffer.buffer,
			m_Buffer.buffer_memory,
			0
		);

		SS_ASSERT(buffer_bind_result == VK_SUCCESS);

		void* mapped_memory = nullptr;

		VkResult map_memory_result = vkMapMemory(
			m_Device,
			m_Buffer.buffer_memory,
			0,
			m_Buffer.size,
			0,
			&mapped_memory
		);

		SS_ASSERT(map_memory_result == VK_SUCCESS);

		memcpy(
			mapped_memory,
			example_input_data,
			m_Buffer.size
		);

		vkUnmapMemory(
			m_Device,
			m_Buffer.buffer_memory
		);

		map_memory_result = vkMapMemory(
			m_Device,
			m_Buffer.buffer_memory,
			0,
			m_Buffer.size,
			0,
			&mapped_memory
		);

		SS_ASSERT(map_memory_result == VK_SUCCESS);

		unsigned int example_output_data[64];

		memcpy(
			example_output_data,
			mapped_memory,
			m_Buffer.size
		);

		vkUnmapMemory(
			m_Device,
			m_Buffer.buffer_memory
		);

	}

	void SandboxVulkan::FreeBufferMemory()
	{
		vkFreeMemory(
			m_Device,
			m_Buffer.buffer_memory,
			nullptr
		);
	}

	void SandboxVulkan::DestroyBuffer()
	{
		vkDestroyBuffer(
			m_Device,
			m_Buffer.buffer,
			nullptr
		);

		FreeBufferMemory();
	}

	void SandboxVulkan::CreateDescriptorPool()
	{
		VkDescriptorSet descriptor_set;
		VkWriteDescriptorSet descriptor_write_set;

		{
			VkDescriptorPoolSize pool_size = {};
			pool_size.type = VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			pool_size.descriptorCount = 1;

			VkDescriptorPoolCreateInfo create_info = {};
			create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
			create_info.poolSizeCount = 1;
			create_info.pPoolSizes = &pool_size;
			create_info.maxSets = 1;

			VkResult result = vkCreateDescriptorPool(
				m_Device,
				&create_info,
				nullptr,
				&m_Descriptor.descriptor_pool
			);

			SS_ASSERT(result == VK_SUCCESS);
		}

		{
			VkDescriptorSetLayoutBinding layout_binding = {};
			layout_binding.binding = 0;
			layout_binding.descriptorType = VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			layout_binding.descriptorCount = 1;
			layout_binding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

			VkDescriptorSetLayoutCreateInfo layout_info = {};
			layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
			layout_info.bindingCount = 1;
			layout_info.pBindings = &layout_binding;

			VkResult result = vkCreateDescriptorSetLayout(
				m_Device,
				&layout_info,
				nullptr,
				&m_Descriptor.descriptor_set_layout
			);

			SS_ASSERT(result == VK_SUCCESS);
		}

		{
			VkDescriptorSetAllocateInfo allocate_info = {};
			allocate_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
			allocate_info.descriptorPool = m_Descriptor.descriptor_pool;
			allocate_info.descriptorSetCount = 1;
			allocate_info.pSetLayouts = &m_Descriptor.descriptor_set_layout;

			VkResult result = vkAllocateDescriptorSets(
				m_Device,
				&allocate_info,
				&descriptor_set
			);

			SS_ASSERT(result == VK_SUCCESS);
		}

		{
			VkDescriptorBufferInfo buffer_info = {};
			buffer_info.buffer = m_Buffer.buffer;
			buffer_info.offset = 0;
			buffer_info.range = m_Buffer.size;

			descriptor_write_set = {};
			descriptor_write_set.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
			descriptor_write_set.dstSet = descriptor_set;
			descriptor_write_set.dstBinding = 0;
			descriptor_write_set.dstArrayElement = 0;
			descriptor_write_set.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
			descriptor_write_set.descriptorCount = 1;
			descriptor_write_set.pBufferInfo = &buffer_info;

			vkUpdateDescriptorSets(
				m_Device,
				1,
				&descriptor_write_set,
				0,
				NULL
			);
		}

	}

	void SandboxVulkan::DestroyDescriptorPool()
	{
		vkDestroyDescriptorSetLayout(
			m_Device,
			m_Descriptor.descriptor_set_layout,
			nullptr
		);

		vkDestroyDescriptorPool(
			m_Device,
			m_Descriptor.descriptor_pool,
			nullptr
		);
	}

}
