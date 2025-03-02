#pragma once
#include "Singleton.h"
#include <chrono>
namespace dae 
{
	class Timer : public Singleton<Timer>
	{
	public:

		double GetDeltaTime() { 
			return m_DeltaTime/1000000000; };
		void SetDeltaTime(double elapsedTime) { m_DeltaTime = elapsedTime; };
	private:
		Timer() = default;
		friend class Singleton<Timer>;
		double m_DeltaTime{};

	};
}


