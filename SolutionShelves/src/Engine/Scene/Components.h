#pragma once

#include <glm/glm.hpp>

#include "Engine/Scene/SceneCamera.h"
#include "Engine/Scene/ScriptableEntity.h"

namespace SolutionShelves
{
	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) { }
	};

	struct TransformComponent
	{
		glm::mat4 Transform{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) { }

		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color) { }
	};

	struct CameraComponent
	{
		SceneCamera Camera;
		bool Primary = true; // TODO: mover para Scene
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};

	struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;
		
		// std::function<void()> InstantiateFunction;
		// std::function<void()> DestroyInstanceFunction;
		void(*InstantiateFunction)(ScriptableEntity*&);
		void(*DestroyInstanceFunction)(ScriptableEntity*&);

		// std::function<void(ScriptableEntity*)> OnCreateFunction;
		// std::function<void(ScriptableEntity*)> OnDestroyFunction;
		// std::function<void(ScriptableEntity*, Timestep)> OnUpdateFunction;
		void(*OnCreateFunction)(ScriptableEntity*);
		void(*OnDestroyFunction)(ScriptableEntity*);
		void(*OnUpdateFunction)(ScriptableEntity*, Timestep);

		template<typename T>
		void Bind()
		{
			// InstantiateFunction = [&]() { Instance = (ScriptableEntity*)(new T()); };
			// DestroyInstanceFunction = [&]() { delete (T*)Instance; Instance = nullptr; };
			InstantiateFunction = [](ScriptableEntity*& instance) { instance = (ScriptableEntity*)(new T()); };
			DestroyInstanceFunction = [](ScriptableEntity*& instance) { delete static_cast<T*>(instance); instance = nullptr; };

			// OnCreateFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnCreate(); };
			// OnDestroyFunction = [](ScriptableEntity* instance) { ((T*)instance)->OnDestroy(); };
			// OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) { ((T*)instance)->OnUpdate(ts); };
			OnCreateFunction = [](ScriptableEntity* instance) { static_cast<T*>(instance)->OnCreate(); };
			OnDestroyFunction = [](ScriptableEntity* instance) { static_cast<T*>(instance)->OnDestroy(); };
			OnUpdateFunction = [](ScriptableEntity* instance, Timestep ts) { static_cast<T*>(instance)->OnUpdate(ts); };
		}
	};
	
}
