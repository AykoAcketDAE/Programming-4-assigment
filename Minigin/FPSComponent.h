#pragma once
#include "Component.h"
#include "TextComponent.h"
namespace dae
{


	class FPSComponent final: public Component
	{
	public:

		FPSComponent() = default;
		~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
		void Update() override;
		void Render() const override {};
		double m_Fps{};

	private:
		TextComponent* m_TextPtr{ nullptr };

	};
}


