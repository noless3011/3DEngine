#pragma once
#include "Component.h"
#include "App.h"
#include "EventListener.h"
#include "MyException.h"

class Entity {
public:
	Entity();
	template<typename T>
	std::shared_ptr<IComponent> getComponent() {};
	template<typename T>
	std::shared_ptr<IComponent> addComponent() {};
	template<typename T>
	void addEventListener(EventAction<T> action);
	int x, y;
private:

	std::vector<std::shared_ptr<IComponent>> components;
};

template<typename T>
inline void Entity::addEventListener(EventAction<T> action)
{
	static_assert(std::is_base_of<EventContext, T>::value, "T must be derived from EventContext");
	std::unique_ptr<EventListener<T>> pListener = std::make_unique<EventListener<T>>(action);
	App::GetInstance().getWindow()->AddListener<T>(pListener);
}
