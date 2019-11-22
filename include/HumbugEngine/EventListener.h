#include <string>

class EventListener
{
public:
	virtual void Update(std::string eventType) = 0;
};