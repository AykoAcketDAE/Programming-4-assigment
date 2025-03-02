#include "RotatorComponent.h"
#include <cmath>
#include "Timer.h"
#define M_PI 3.14159265

dae::RotatorComponent::RotatorComponent()
{
}

void dae::RotatorComponent::Update()
{
	if (m_Angle > 360) m_Angle -= 360;
	m_Angle += static_cast <float>((2 * M_PI) * Timer::GetInstance().GetDeltaTime());
	float x = static_cast<float>( m_Radius * std::cos(m_Angle));
	float y = static_cast<float>( m_Radius * std::sin(m_Angle));

	GetOwner()->SetLocalPosition({ x,y,0 });
}
