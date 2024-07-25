#pragma once

#include "Event.h"

template<typename T> using EventAction = std::function<bool(T)>;

class IEventListener {
public:
	virtual ~IEventListener() = default;
	virtual bool Update(EventContext* e) = 0;
};

template<typename T>
class EventListener : public IEventListener {
public:
	EventListener(EventAction<T> action)
	{
		static_assert(std::is_base_of<EventContext, T>::value, "T must be derived from Event");
		eventAction = action;
	};
	virtual bool Update(EventContext* e) override
	{
		return eventAction(*(T*)e);
	};
private:
	EventAction<T> eventAction;
};
