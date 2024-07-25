#pragma once
#include "stdafx.h"
#include "Event.h"
#include "EventListener.h"

class EventDispatcher {
public:
	template<typename T>
	void AddEventListener(EventAction<T> action) noexcept;
	template<typename T>
	void AddEventListener(std::unique_ptr<EventListener<T>> listener) noexcept;
	template<typename T>
	void RemoveEventListener() noexcept;
	void DispatchEvent(EventContext* e) noexcept;
private:
	std::unordered_map<const char*, std::unique_ptr<IEventListener>> listeners;
};

template<typename T>
inline void EventDispatcher::AddEventListener(EventAction<T> action) noexcept
{
	static_assert(std::is_base_of<EventContext, T>::value, "T must be derived from EventContext");
	const char* eventType = typeid(T).name();
	std::unique_ptr<EventListener<T>>listener = std::make_unique<EventListener<T>>(action);
	listeners.insert(std::make_pair(eventType, listener));
}

template<typename T>
inline void EventDispatcher::AddEventListener(std::unique_ptr<EventListener<T>> listener) noexcept
{
	listeners.insert(std::make_pair(typeid(T).name(), std::move(listener)));
}

template<typename T>
inline void EventDispatcher::RemoveEventListener() noexcept
{
	static_assert(std::is_base_of<EventContext, T>::value, "T must be derived from EventListener");
	const char* eventType = typeid(T).name();
	listeners.erase(eventType);
}
