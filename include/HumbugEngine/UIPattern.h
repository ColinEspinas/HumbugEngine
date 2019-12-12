#pragma once
#include <string>
#include <vector>
#include <array>

class UIPattern
{
public:
    UIPattern(std::string _fileName);

    std::vector<float> verts;
    std::vector<float> uvs;
    std::string texName;

private:
    void AddTriangle(std::array<std::array<float,2>,3> _vts,
        std::array<std::array<float,2>,3> _uvs);
};