#include "Rendercomponent.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::Rendercomponent::Rendercomponent(const std::string& fullPath)
	:m_Path{fullPath}
{
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(fullPath);
}

void dae::Rendercomponent::Render() const
{
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, GetOwner()->GetWorldPosition().x, GetOwner()->GetWorldPosition().y);
}

void dae::Rendercomponent::SetTexture(const std::string& fullPath)
{
	dae::ResourceManager::GetInstance().LoadTexture(fullPath);
	m_Path = fullPath;
}
