#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>

namespace dae
{
	class Texture2D;
	class Component;
	
	class GameObject final
	{


	public:
		virtual void Update();
		virtual void Render() const;

		void SetPosition(float x, float y);

		template<typename Comp, typename... Args>
		void AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of<Component, Comp>::value, "ComponentType must be derived from Component");

			auto component = std::make_unique<Comp>(std::forward<Args>(args)...);
			component->m_Owner = this;
			
			m_ComponentPtrList.push_back(std::move(component));
		};

		template<typename Comp>
		void RemoveComponent(Comp* component)
		{
			static_assert(std::is_base_of<Component, Comp>::value, "ComponentType must be derived from Component");

			auto it = std::remove_if(m_ComponentPtrList.begin(), m_ComponentPtrList.end(),
				[](const std::unique_ptr<Component>& component)
				{
					return dynamic_cast<Comp*>(component.get()) != nullptr;
				});

			if (it != m_ComponentPtrList.end())
			{
				m_ComponentPtrList.erase(it, m_ComponentPtrList.end());
			}
			
				
		};

		template<typename Comp>
		Comp* GetComponent()
		{
			static_assert(std::is_base_of<Component, Comp>::value, "ComponentType must be derived from Component");

			for (const auto& component : m_ComponentPtrList)  
			{
				if (auto castedComp = dynamic_cast<Comp*>(component.get())) 
				{
					return castedComp; 
				}
			}
			return nullptr;  
		};

		template<typename Comp>
		bool HasComponent()
		{
			static_assert(std::is_base_of<Component, Comp>::value, "ComponentType must be derived from Component");

			for (const auto& component : m_ComponentPtrList)
			{
				if (dynamic_cast<Comp*>(component.get()))
				{
					return true;
				}
			}
			return false;
		}

		void SetParent(GameObject* parent, bool keepWorldPosition);
		GameObject* GetParent() const { return m_Parent; };
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(const GameObject* parent);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		const glm::vec3 GetWorldPosition() const { return m_WorldPosition; }
		void SetLocalPosition(const glm::vec3& pos);
		void UpdateWorldPosition();
		void SetPositionDirty() { m_PositionIsDirty = true; };

		
	private:
		Transform m_Transform{};

		bool m_IsRendering{ false };

		std::vector<std::unique_ptr<Component>> m_ComponentPtrList{};

		GameObject* m_Parent{nullptr};
		std::vector<GameObject*> m_Children{};

		glm::vec3 m_WorldPosition{};
		glm::vec3 m_LocalPosition{};
		bool m_PositionIsDirty{ false };
	};
}
