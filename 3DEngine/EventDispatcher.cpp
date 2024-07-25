#include "stdafx.h"
#include "EventDispatcher.h"

void EventDispatcher::DispatchEvent(EventContext* e) noexcept
{
	for (auto& pair : listeners) {
		pair.second->Update(e);
	}
}