#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update() = 0;
		virtual void Render() const = 0;
	protected:
		GameObject* m_Owner{};
		Component() = default;
	private:
		
		friend class GameObject;
		
	};
}

