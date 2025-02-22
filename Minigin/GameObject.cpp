#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_Parent == parent)
		return;
	if (parent == nullptr)
		SetLocalPosition(GetWorldPosition());
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}
	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
}

void dae::GameObject::AddChild(GameObject* child)
{
	m_Children.push_back(child);
	child->UpdateWorldPosition();
}

void dae::GameObject::RemoveChild(GameObject* child)
{
	if (!child) return;
	std::erase(m_Children, child);

}

bool dae::GameObject::IsChild(const GameObject* parent)
{
	if (!parent) return false; 

	return std::find(parent->m_Children.begin(), parent->m_Children.end(), this) != parent->m_Children.end();
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::SetLocalPosition(const glm::vec3& Pos)
{
	m_LocalPosition = Pos;
	SetPositionDirty();
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_Parent == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = m_Parent->GetWorldPosition() + m_LocalPosition;
	}
	m_PositionIsDirty = false;
}

void dae::GameObject::Update()
{
	if (m_PositionIsDirty) UpdateWorldPosition();
	for (const auto& comp : m_ComponentPtrList)
	{
		comp->Update();
	}
	for (const auto& child : m_Children)
	{
		child->Update();
	}
}

void dae::GameObject::Render() const 
{
	
	for (const auto& component : m_ComponentPtrList) {
		component->Render();
	}
	
	for (const auto& child : m_Children) {
		child->Render();
	}
	
}


void dae::GameObject::SetPosition(float x, float y)
{
	m_WorldPosition = { x,y,0 };
}
