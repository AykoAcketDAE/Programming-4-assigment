#include "FPSComponent.h"
#include "Timer.h"


void dae::FPSComponent::Update()
{
	if (m_TextPtr == nullptr) m_TextPtr = m_Owner->GetComponent<TextComponent>();
	m_Fps = 1000000000.f / Timer::GetInstance().GetDeltaTime();
	m_TextPtr->SetText(std::to_string(m_Fps) + " fps");
}


