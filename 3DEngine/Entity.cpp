#include "stdafx.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::Entity(float x, float y, float z)
{
}

Entity::~Entity()
{
}

template<typename T>
std::shared_ptr<T> Entity::GetComponent()
{
	for (const auto& component : componentList)
	{
		if (typeid(component) == typeid(T))
		{
			return std::shared_ptr<T>(component);
		}
	}
	return nullptr;
	throw EngineException();
}

template<typename T>
void Entity::AddComponent(T addedComponent)
{
	for (const auto& component : componentList)
	{
		if (typeid(addedComponent) == typeid(component))
		{
			throw EngineException();
			return;
		}
	}
	componentList.push_back(addedComponent);
}