#include "Rendercomponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::Rendercomponent::Rendercomponent(const std::string& fullPath,float x,float y)
	:m_Path{fullPath},xPos{x},yPos{y}
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fullPath);
}

void dae::Rendercomponent::Render() const
{
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, xPos, yPos);
}

void dae::Rendercomponent::SetTexture(const std::string& fullPath)
{
	dae::ResourceManager::GetInstance().LoadTexture(fullPath);
	m_Path = fullPath;
}
