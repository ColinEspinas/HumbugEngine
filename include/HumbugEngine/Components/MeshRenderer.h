#pragma once
#include "HumbugEngine/Components/Component.h"
#include "HumbugEngine/Ressources/Mesh.h"

class MeshRenderer : public Component
{
private:
    PMeshVec m_meshs;

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
    std::shared_ptr<Mesh> GetMesh(int _index);

    void Use();
};