#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (const auto& comp : m_ComponentPtrList)
	{
		comp->Update();
	}
}

void dae::GameObject::Render() const 
{
	for (const auto& component : m_ComponentPtrList) {
		component->Render();
	}
	
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
