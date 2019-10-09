#pragma once
#include "HumbugEngine/GameHeader.h"
#include "HumbugEngine/Vector.h"
#include "HumbugEngine/Camera.h"
#include "HumbugEngine/Sphere.h"
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
	template<class C = Component> void AddComponent();
	void AddComponent(std::shared_ptr<Component> c);
	// Remove Component
	void RemoveComponent(std::string name);
	template<class C = Component> void RemoveComponent();
	void RemoveComponent(std::shared_ptr<Component> c);


	// Debug:

	void DebugDraw(const Camera& cam);


	// Pos info:

	Matrix4 LocalToWorld() const;
	Matrix4 WorldToLocal() const;
	Vector3 Forward() const;

//Casts
	// virtual Physical* AsPhysical() { return nullptr; }
	// const Physical* AsPhysical() const { return const_cast<Object*>(this)->AsPhysical(); }

// Physical scale, only updated by portal scale changes
//   float p_scale;

//   std::shared_ptr<Mesh> mesh;
//   std::shared_ptr<Texture> texture;
//   std::shared_ptr<Shader> shader;
//   std::shared_ptr<Material> material;
};
typedef std::vector<std::shared_ptr<Object>> PObjectVec;

inline std::shared_ptr<Component> Object::GetComponent(std::string name)
{
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
	for (auto component : m_components) {
		if (std::dynamic_pointer_cast<C>(component)) {
			comps.push_back(component);
		}
	}
	return comps;
}

template<class C>
inline void Object::AddComponent()
{
	m_components.push_back(std::make_shared<C>());
}

inline void Object::AddComponent(std::shared_ptr<Component> c)
{
	if (c != nullptr) {
		m_components.push_back(c);
	}
}

inline void Object::RemoveComponent(std::string name)
{
	for (auto component : m_components) {
		if (component->GetName() == name) {
			m_components.erase(component);
			return;
		}
	}
}

template<class C>
inline void Object::RemoveComponent()
{
	for (auto component : m_components) {
		if (std::dynamic_pointer_cast<C>(component)) {
			m_components.erase(component);
			return;
		}
	}
}

inline void Object::RemoveComponent(std::shared_ptr<Component> c)
{
	for (auto component : m_components) {
		if (component == c) {
			m_components.erase(component);
			return;
		}
	}
}