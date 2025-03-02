#pragma once
#include "Component.h"

namespace dae
{
	class Component;

	class RotatorComponent final : public Component
	{
	public:
		RotatorComponent();

		void Update();
		void Render() const {};
	private:

		float m_Radius{100};
		float m_Angle{};
	
	};
}

