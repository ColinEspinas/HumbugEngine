#include "HumbugEngine/Core/Scene.h"

// Scene Constructor
Scene::Scene()
    : m_Objects(0)
{
}

// Add Object to Scene
void Scene::AddObject(std::shared_ptr<Object> Obj)
{
    m_Objects.push_back(Obj);
}

// Remove Object from Scene
void Scene::RemoveObject(std::shared_ptr<Object> Obj)
{
    for (int ii = 0; ii < m_Objects.size(); ii++)
        if (m_Objects[ii] == Obj)
        {
            m_Objects.erase(m_Objects.begin() + ii);
            break;
        }
}

// Get Object from Scene (at specified index)
std::shared_ptr<Object> Scene::GetObject(int index)
{
    if (index < 0 || index >= m_Objects.size())
        return nullptr;
    return m_Objects[index];
}

// Get Amount of Object in Scene
int Scene::GetObjectAmount()
{
    return m_Objects.size();
}