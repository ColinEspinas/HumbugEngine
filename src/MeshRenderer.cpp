#include "HumbugEngine/Components/MeshRenderer.h"
#include "HumbugEngine/Utils/Resources.h"
#include "HumbugEngine/Objects/Player.h"


// Decrement Each Mesh Index & Remove if Index
void MeshRenderer::ComputeMaterial_withRemovalAt(int index)
{
    for (auto mat : m_materials)
        for (int ii = 0; ii < mat.second.size(); ii)
        {
            if (mat.second[ii] == index)
                mat.second.erase(mat.second.begin() + ii);
            else
            {
                if (mat.second[ii] > index)
                    mat.second[ii]--;
                ii++;
            }
        }
}

// Constructor
MeshRenderer::MeshRenderer(PMeshVec _meshs)
    : Component("MeshRenderer"), m_meshs(_meshs), m_materials{}
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
            ComputeMaterial_withRemovalAt(ii);
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
            ComputeMaterial_withRemovalAt(ii);
            break;
        }
}

// Remove All Mesh by Mesh
void MeshRenderer::RemoveAllMesh(std::shared_ptr<Mesh> _mesh)
{
    for (int ii = 0; ii < m_meshs.size(); ii)
    {
        if (m_meshs[ii] == _mesh)
        {
            m_meshs.erase(m_meshs.begin() + ii);
            ComputeMaterial_withRemovalAt(ii);
        }
        else ii++;
    }
}

// Remove All Mesh by Path
void MeshRenderer::RemoveAllMesh(std::string _path)
{
    for (int ii = 0; ii < m_meshs.size(); ii)
    {
        if (m_meshs[ii]->getPath() == _path)
        {
            m_meshs.erase(m_meshs.begin() + ii);
            ComputeMaterial_withRemovalAt(ii);
        }
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

// Add Material as Material
void MeshRenderer::AddMaterial(std::shared_ptr<Material> _mat)
{
    for (auto mat : m_materials)
        if (mat.first == _mat)
            return;
    m_materials.push_back({_mat,std::vector<int>{}});
}

// Bind Material to Mesh by Material
void MeshRenderer::BindMaterial(std::shared_ptr<Material> _mat, std::shared_ptr<Mesh> _mesh)
{
    for (auto mat : m_materials)
        if (mat.first == _mat)
        {
            for (auto iMesh : mat.second)
                if (GetMesh(iMesh) == _mesh)
                    return;
            for (int ii = 0; ii < m_meshs.size(); ii++)
                if (m_meshs[ii] == _mesh)
                    mat.second.push_back(ii);
        }
}

// Bind Material to Mesh by Material
void MeshRenderer::BindMaterial(int _index, std::shared_ptr<Mesh> _mesh)
{
    if (_index < 0 || _index >= m_materials.size())
        return;
    for (auto iMesh : m_materials[_index].second)
        if (GetMesh(iMesh) == _mesh)
            return;
    for (int ii = 0; ii < m_meshs.size(); ii++)
        if (m_meshs[ii] == _mesh)
            m_materials[_index].second.push_back(ii);
}

// Remove Material with Material
void MeshRenderer::RemoveMaterial(std::shared_ptr<Material> _mat)
{
    for (int ii = 0; ii < m_materials.size(); ii++)
        if (m_materials[ii].first == _mat)
            m_materials[ii].second.clear();
}
    
// Remove Material with Index
void MeshRenderer::RemoveMaterial(int _index)
{
    if (_index < 0 || _index >= m_materials.size())
        return;
    m_materials[_index].second.clear();
}

// Remove Material with Mesh
void MeshRenderer::RemoveMaterial(std::shared_ptr<Mesh> _mesh)
{
    for (auto Mat : m_materials)
        for (int ii = 0; ii < Mat.second.size(); ii++)
            if (m_meshs[Mat.second[ii]] == _mesh)
                Mat.second.clear();
}

// Remove All Material
void MeshRenderer::RemoveAllMaterial()
{
    for (auto mat : m_materials)
        mat.second.clear();
}

// Clean All Material : Remove Non-Binded Materials
void MeshRenderer::CleanMaterial()
{
    for (int ii = 0; ii < m_materials.size(); ii)
    {
        if (m_materials[ii].second.empty())
            m_materials.erase(m_materials.begin() + ii);
        else ii++;
    }
}

// Get Material from Mesh
std::shared_ptr<Material> MeshRenderer::GetMaterial(std::shared_ptr<Mesh> _mesh)
{
    for (auto mat : m_materials)
        for (int iMesh : mat.second)
            if (GetMesh(iMesh) == _mesh)
                return mat.first;
    return nullptr;
}

// Get All Materials
std::vector<std::shared_ptr<Material>> MeshRenderer::GetAllMaterial()
{
    std::vector<std::shared_ptr<Material>> res(0);
    for (auto Mat : m_materials)
        res.push_back(Mat.first);
    return res;
}

// Get Material at Index
std::shared_ptr<Material> MeshRenderer::GetMaterial(int _index)
{
    if (_index < 0 || _index >= m_materials.size())
        return nullptr;
    return m_materials[_index].first;
}

// Get All Mesh from Material
PMeshVec MeshRenderer::GetAllMesh(std::shared_ptr<Material> _mat)
{
    PMeshVec res(0);
    for (auto mat : m_materials)
        if (mat.first == _mat)
            for (int iMesh : mat.second)
                res.push_back(m_meshs[iMesh]);
    return res;
}

// Verify if Contain Mesh
bool MeshRenderer::Contain(std::shared_ptr<Mesh> _mesh)
{
    for (auto mesh : m_meshs)
        if (mesh == _mesh)
            return true;
    return false;
}

// Verify if Contain Material
bool MeshRenderer::Contain(std::shared_ptr<Material> _mat)
{
    for (auto mat : m_materials)
        if (mat.first == _mat)
            return true;
    return false;
}

// Use Mesh Renderer
void MeshRenderer::Render()
{
    for (auto M : m_meshs)
        M->Use();
}

// Draw Meshes
void MeshRenderer::Draw(const Camera& cam, const Matrix4 m, const Matrix4 mv, const Matrix4 mvp)
{
    for (auto Mesh : m_meshs)
    {
        if (Mesh->shader) {
            Mesh->shader->Use();
            if (Mesh->texture) {
                Mesh->texture->Use();
            }

            if (GetMaterial(Mesh) != nullptr)
            {
                GetMaterial(Mesh)->Bind(Mesh->shader);
                GetMaterial(Mesh)->Use();
            }

            Mesh->shader->SetM(m.m);
            Mesh->shader->SetCam(GH_PLAYER->CamToWorld());
            Mesh->shader->SetMVP(mvp.m, mv.m);
            Mesh->Draw();
        }
    }
}