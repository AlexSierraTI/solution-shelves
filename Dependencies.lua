
-- Solution Shelves Dependencies

VULKAN_SDK = os.getenv("VULKAN_SDK")

IncludeDir = {}
IncludeDir["stb_image"] = "%{wks.location}/SolutionShelves/vendor/stb_image"
IncludeDir["yaml_cpp"] = "%{wks.location}/SolutionShelves/vendor/yaml-cpp/include"
IncludeDir["GLFW"] = "%{wks.location}/SolutionShelves/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/SolutionShelves/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/SolutionShelves/vendor/ImGui"
IncludeDir["ImGuizmo"] = "%{wks.location}/SolutionShelves/vendor/ImGuizmo"
IncludeDir["glm"] = "%{wks.location}/SolutionShelves/vendor/glm"
IncludeDir["entt"] = "%{wks.location}/SolutionShelves/vendor/entt/include"
IncludeDir["shaderc"] = "%{wks.location}/SolutionShelves/vendor/shaderc/include"
IncludeDir["SPIRV_Cross"] = "%{wks.location}/SolutionShelves/vendor/SPIRV-Cross"
IncludeDir["VulkanSDK"] = "%{VULKAN_SDK}/Include"

LibraryDir = {}

LibraryDir["VulkanSDK"] = "%{VULKAN_SDK}/Lib"
LibraryDir["VulkanSDK_Debug"] = "%{wks.location}/SolutionShelves/vendor/VulkanSDK/Lib"

Library = {}
Library["Vulkan"] = "%{LibraryDir.VulkanSDK}/vulkan-1.lib"
Library["VulkanUtils"] = "%{LibraryDir.VulkanSDK}/VkLayer_utils.lib"

Library["ShaderC_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/shaderc_sharedd.lib"
Library["SPIRV_Cross_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-cored.lib"
Library["SPIRV_Cross_GLSL_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/spirv-cross-glsld.lib"
Library["SPIRV_Tools_Debug"] = "%{LibraryDir.VulkanSDK_Debug}/SPIRV-Toolsd.lib"

Library["ShaderC_Release"] = "%{LibraryDir.VulkanSDK}/shaderc_shared.lib"
Library["SPIRV_Cross_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-core.lib"
Library["SPIRV_Cross_GLSL_Release"] = "%{LibraryDir.VulkanSDK}/spirv-cross-glsl.lib"
