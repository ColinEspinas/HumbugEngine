#pragma once
#include "HumbugEngine/Utils/GameHeader.h"
#include "HumbugEngine/Utils/Vector.h"
#include "HumbugEngine/Components/Camera.h"
#include "HumbugEngine/Ressources/Sphere.h"
#include "HumbugEngine/Components/Component.h"
#include <string>
#include <vector>
#include <memory>

//Forward declarations
class Physical;
class Mesh;
class Texture;
class Shader;
class Material;

class Object {
protected:
	PComponentVec m_components;

	virtual bool allowForComponents() { return true; }

public:
	Vector3 m_pos;
	Vector3 m_euler;
	Vector3 m_scale;
	
	Object();
	virtual ~Object() {}

	virtual void Reset();

	virtual void Start() {};
	virtual void Update() {};
	
	virtual void Draw(const Camera& cam, uint32_t curFBO);

	virtual void OnHit(Object& other, Vector3& push) {};


	// Components Methods:

	// Get single component
	std::shared_ptr<Component> GetComponent(std::string name);
	template<class C = Component> std::shared_ptr<Component> GetComponent();
	// Get multiple components
	PComponentVec GetComponents(std::string name);
	template<class C = Component> PComponentVec GetComponents();
	// Add component
	//void AddComponent(std::string name);
	//	template<class C = Component, class ...Args> void AddComponent(C obj, Args... args);
	void AddComponent(std::shared_ptr<Component> c);
	// Remove Component
	void RemoveComponent(std::string name);
	template<class C = Component> void RemoveComponent();
	void RemoveComponent(std::shared_ptr<Component> c);
	// Remove ComponentS
	void RemoveComponents(std::string name);
	template<class C = Component> void RemoveComponents();
	// Verification of Component
	template<class C = Component> bool Contain();
	bool Contain(std::string _name);


	// Debug:

	void DebugDraw(const Camera& cam);

	// Pos info:

	Matrix4 LocalToWorld() const;
	Matrix4 WorldToLocal() const;
	Vector3 Forward() const;

	// Physical scale, only updated by portal scale changes
   	float p_scale;

//Casts
	// virtual Physical* AsPhysical() { return nullptr; }
	// const Physical* AsPhysical() const { return const_cast<Object*>(this)->AsPhysical(); }

//   std::shared_ptr<Mesh> mesh;
//   std::shared_ptr<Texture> texture;
//   std::shared_ptr<Shader> shader;
//   std::shared_ptr<Material> material;
};
typedef std::vector<std::shared_ptr<Object>> PObjectVec;

inline std::shared_ptr<Component> Object::GetComponent(std::string name)
{
	if (!allowForComponents()) return nullptr;

	for (auto component : m_components) {
		if (component->GetName() == name) {
			return component;
		}
	}
	return nullptr;
}

template<class C>
inline std::shared_ptr<Component> Object::GetComponent()
{
	for (auto component : m_components) {
		if (std::dynamic_pointer_cast<C>(component)) {
			return component;
		}
	}
	return nullptr;
}

inline PComponentVec Object::GetComponents(std::string name)
{
	PComponentVec comps;
	for (auto component : m_components) {
		if (component->GetName() == name) {
			comps.push_back(component);
		}
	}
	return comps;
}

template<class C>
inline PComponentVec Object::GetComponents()
{
	PComponentVec comps;
	for (int ii = 0; ii < m_components.size(); ii++) {
		if (std::dynamic_pointer_cast<C>(m_components[ii])) {
			comps.push_back(m_components[ii]);
		}
	}
	return comps;
}

//template<class C, class ...Args>
//inline void Object::AddComponent(C obj, Args... args)
//{
//	if (!allowForComponents()) return;
//
//	m_components.push_back(std::make_shared<C>(args));
//}

inline void Object::AddComponent(std::shared_ptr<Component> c)
{
	if (!allowForComponents()) return;

	if (c != nullptr) {
		m_components.push_back(c);
	}
}

inline void Object::RemoveComponent(std::string name)
{
	if (!allowForComponents()) return;

	for (int ii = 0; ii < m_components.size(); ii++) {
		if (m_components[ii]->GetName() == name) {
			m_components.erase(m_components.begin() + ii);
			return;
		}
	}
}

template<class C>
inline void Object::RemoveComponent()
{
	if (!allowForComponents()) return;

	for (int ii = 0; ii < m_components.size(); ii++) {
		if (std::dynamic_pointer_cast<C>(m_components[ii])) {
			m_components.erase(m_components.begin() + ii);
			return;
		}
	}
}

inline void Object::RemoveComponent(std::shared_ptr<Component> c)
{
	if (!allowForComponents()) return;

	for (int ii = 0; ii < m_components.size(); ii++) {
		if (m_components[ii] == c) {
			m_components.erase(m_components.begin() + ii);
			return;
		}
	}
}

inline void Object::RemoveComponents(std::string name)
{
	if (!allowForComponents()) return;

	for (int ii = 0; ii < m_components.size(); ii)
	{
		if (m_components[ii]->GetName() == name)
			m_components.erase(m_components.begin() + ii);
		else ii++;
	}
}

template<class C>
inline void Object::RemoveComponents()
{
	if (!allowForComponents()) return;
	
	for (int ii = 0; ii < m_components.size(); ii)
	{
		if (std::dynamic_pointer_cast<C>(m_components[ii]))
			m_components.erase(m_components.begin() + ii);
		else ii++;
	}
}

template<class C>
inline bool Object::Contain()
{
	return (GetComponent<C>() != nullptr);
}

inline bool Object::Contain(std::string _name)
{
	return (GetComponent(_name) != nullptr);
}




// Casts
namespace ObjectCast
{
	template<class C>
	inline std::shared_ptr<C> Cast(std::shared_ptr<Object> obj)
	{
		return std::dynamic_pointer_cast<C>(obj);
	}

	template<class C>
	inline bool isFrom(std::shared_ptr<Object> obj)
	{
		return (Cast<C>(obj) != nullptr);
	}
}