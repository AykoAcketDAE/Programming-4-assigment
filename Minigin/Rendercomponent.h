#pragma once
#include "Component.h"
#include <string>
#include "Texture2D.h"
struct SDL_Texture;
namespace dae 
{
	class Rendercomponent final :public Component
	{
	public:
		Rendercomponent(const std::string& fullPath,float x,float y);

		void Update() {};
		void Render()const;

		void SetTexture(const std::string& fullPath);
		void SetPosition(float x, float y) { xPos = x; yPos = y; };

	private:
		
		std::string m_Path{};
		float xPos{};
		float yPos{};
		std::shared_ptr<Texture2D> m_Texture{};
	};
}


