#pragma once
#include "Component.h"
#include "MyException.h"

class Entity {
public:
	Entity();
	Entity(float x, float y, float z);
	~Entity();

public:
	std::string name;

	std::vector<std::string> tags;//will create a Tag class in the future

public:
	template <typename T>
	std::shared_ptr<T> GetComponent();
	template <typename T>
	void AddComponent(T addedComponent);
private:
	std::vector<std::variant<IComponent>> componentList;
};
