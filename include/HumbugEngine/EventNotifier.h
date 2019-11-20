#include "HumbugEngine/EventListener.h"
#include <string>
#include <list>
#include <memory>

class EventNotifier
{
private:
	std::list<std::shared_ptr<EventListener>> m_listeners;
public:
	EventNotifier(std::shared_ptr<EventListener> listener);
	EventNotifier(std::list<std::shared_ptr<EventListener>> listeners);

	void Attach(std::shared_ptr<EventListener> listener);
	void Detach(std::shared_ptr<EventListener> listener);

	void Notify(std::string eventType);
};