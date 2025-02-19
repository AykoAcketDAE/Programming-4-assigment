#pragma once
#include "Singleton.h"

namespace dae 
{
	class Timer : public Singleton<Timer>
	{
	public:

		float GetDeltaTime() { return m_DeltaTime; };
		void SetDeltaTime(float elapsedTime) { m_DeltaTime = elapsedTime; };
	private:
		Timer() = default;
		friend class Singleton<Timer>;
		float m_DeltaTime{};

	};
}


