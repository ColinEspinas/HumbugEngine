#pragma once
#include <string>
#include <vector>
#include <memory>

class Component
{
protected:
	// size_t m_uid;
	std::string m_name;
public:
	Component(std::string name) : m_name(name) {}
	~Component() {}

	std::string GetName() { return m_name; }


	virtual int Use() = 0;
	virtual void Start() {}
	virtual void Update() {}
};
typedef std::vector<std::shared_ptr<Component>> PComponentVec;




// Casts
namespace ComponentCast
{
	template<class C>
	inline std::shared_ptr<C> Cast(std::shared_ptr<Component> comp)
	{
		return std::dynamic_pointer_cast<C>(comp);
	}

	template<class C>
	inline bool isFrom(std::shared_ptr<Component> comp)
	{
		return (Cast<C>(comp) != nullptr);
	}
}