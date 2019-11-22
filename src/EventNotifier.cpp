#include "HumbugEngine/EventNotifier.h"

EventNotifier::EventNotifier(std::shared_ptr<EventListener> listener) {
	Attach(listener);
}

EventNotifier::EventNotifier(std::list<std::shared_ptr<EventListener>> listeners) {
	for (auto listener : listeners)
	{
		Attach(listener);
	}
}

void EventNotifier::Attach(std::shared_ptr<EventListener> listener) {
	m_listeners.push_back(listener);
}

void EventNotifier::Detach(std::shared_ptr<EventListener> listener) {
	std::list<std::shared_ptr<EventListener>>::iterator it = m_listeners.begin();
	while (it != m_listeners.end()) {
		if (*it == listener) {
			m_listeners.erase(it++);
		}
		else {
			++it;
		}
	}
}

void EventNotifier::Notify(std::string eventType) {
	for (auto listener : m_listeners) {
		listener->Update(eventType);
	}
}