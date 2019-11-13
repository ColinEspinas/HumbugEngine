#pragma once
#include "HumbugEngine/Components/Component.h"
#include "HumbugEngine/Ressources/Mesh.h"
#include <utility>

class MeshRenderer : public Component
{
private:
    PMeshVec m_meshs;
    std::vector<std::pair<std::shared_ptr<Material>, std::vector<int>>> m_materials;

    void ComputeMaterial_withRemovalAt(int index);

public:
    MeshRenderer(PMeshVec _meshs = {});
    
    void AddMesh(std::shared_ptr<Mesh> _mesh);
    void AddMesh(std::string _path);
    void RemoveMesh(std::shared_ptr<Mesh> _mesh);
    void RemoveMesh(std::string _path);
    void RemoveAllMesh(std::shared_ptr<Mesh> _mesh);
    void RemoveAllMesh(std::string _path);

    std::shared_ptr<Mesh> GetMesh(std::string _path);
    PMeshVec GetAllMesh(std::string _path);
    PMeshVec GetAllMesh() { return m_meshs; }
    std::shared_ptr<Mesh> GetMesh(int _index);

    void AddMaterial(std::shared_ptr<Material> _mat);
    void BindMaterial(std::shared_ptr<Material> _mat, std::shared_ptr<Mesh> _mesh);     // Unsafe
    void BindMaterial(int _index, std::shared_ptr<Mesh> _mesh);                         // Unsafe
    void RemoveMaterial(std::shared_ptr<Material> _mat);
    void RemoveMaterial(int _index);
    void RemoveMaterial(std::shared_ptr<Mesh> _mesh);
    void RemoveAllMaterial();
    void CleanMaterial();

    std::shared_ptr<Material> GetMaterial(std::shared_ptr<Mesh> _mesh);
    std::vector<std::shared_ptr<Material>> GetAllMaterial();
    std::shared_ptr<Material> GetMaterial(int _index);

    PMeshVec GetAllMesh(std::shared_ptr<Material> _mat);
    bool Contain(std::shared_ptr<Mesh> _mesh);
    bool Contain(std::shared_ptr<Material> _mat);

    void Render();
    int Use() override { return 0; }
    void Draw(const Camera& cam, const Matrix4 m, const Matrix4 mv, const Matrix4 mvp);
};