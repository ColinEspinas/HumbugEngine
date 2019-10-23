#include "HumbugEngine/Components/MeshRenderer.h"

// Constructor
MeshRenderer::MeshRenderer(PMeshVec _meshs)
    : Component("MeshRenderer"), m_meshs(_meshs)
{}

// Add Mesh by Mesh
void MeshRenderer::AddMesh(std::shared_ptr<Mesh> _mesh)
{
    m_meshs.push_back(_mesh);
}

// Add Mesh by Path
void MeshRenderer::AddMesh(std::string _path)
{
    m_meshs.push_back(std::make_shared<Mesh>(_path));
}

// Remove Mesh by Mesh
void MeshRenderer::RemoveMesh(std::shared_ptr<Mesh> _mesh)
{
    for (int ii = 0; ii < m_meshs.size(); ii++)
        if (m_meshs[ii] == _mesh)
        {
            m_meshs.erase(m_meshs.begin() + ii);
            break;
        }
}

// Remove Mesh by Path
void MeshRenderer::RemoveMesh(std::string _path)
{
    for (int ii = 0; ii < m_meshs.size(); ii++)
        if (m_meshs[ii]->getPath() == _path)
        {
            m_meshs.erase(m_meshs.begin() + ii);
            break;
        }
}

// Remove All Mesh by Mesh
void MeshRenderer::RemoveAllMesh(std::shared_ptr<Mesh> _mesh)
{
    for (int ii = 0; ii < m_meshs.size(); ii)
    {
        if (m_meshs[ii] == _mesh)
            m_meshs.erase(m_meshs.begin() + ii);
        else ii++;
    }
}

// Remove All Mesh by Path
void MeshRenderer::RemoveAllMesh(std::string _path)
{
    for (int ii = 0; ii < m_meshs.size(); ii)
    {
        if (m_meshs[ii]->getPath() == _path)
            m_meshs.erase(m_meshs.begin() + ii);
        else ii++;
    }
}

// Get Mesh by Path
std::shared_ptr<Mesh> MeshRenderer::GetMesh(std::string _path)
{
    for (auto M : m_meshs)
        if (M->getPath() == _path)
            return M;
    return nullptr;
}

// Get All Mesh by Path
PMeshVec MeshRenderer::GetAllMesh(std::string _path)
{
    PMeshVec res(0);
    for (auto M : m_meshs)
        if (M->getPath() == _path)
            res.push_back(M);
    return res;
}

// Get Mesh by Index
std::shared_ptr<Mesh> MeshRenderer::GetMesh(int _index)
{
    if (_index >= 0 && _index < m_meshs.size())
        return m_meshs[_index];
    return nullptr;
}

// Use Mesh Renderer
void MeshRenderer::Use()
{
    for (auto M : m_meshs)
        M->Use();
}