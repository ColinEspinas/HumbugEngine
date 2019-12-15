#include "HumbugEngine/UIPattern.h"
#include "HumbugEngine/GameHeader.h"
#include <fstream>
#include <sstream>


UIPattern::UIPattern(std::string _fileName)
    : texName("")
{
    // Open the file for reading
    std::ifstream fin(std::string("assets/uipatterns/") + _fileName + ".heui");
    if (!fin) return;

    // Init
    std::vector<std::array<float,2>> verts_palette;
    std::vector<std::array<float,2>> uvs_palette;

    // Read File
    std::string line;
    while (!fin.eof())
    {
        std::getline(fin, line);

        // Find Texture Name
        if (line.find("texture ") == 0)
        {
            std::stringstream ss(line.c_str() + 8);
            ss >> texName;
        }

        // Read Vertices
        else if (line.find("v ") == 0)
        {
            std::stringstream ss(line.c_str() + 2);
            float x, y;
            ss >> x >> y;
            verts_palette.push_back({x,y});
        }

        // Read Texture
        else if (line.find("u ") == 0)
        {
            std::stringstream ss(line.c_str() + 2);
            float x, y;
            ss >> x >> y;
            uvs_palette.push_back({x,y});
        }

        // Read Quad
        else if (line.find("q ") == 0)
        {
            // Remove '/'
            for (size_t ii = 1; ii < line.size(); ++ii)
                if (line[ii] == '/')
                    line[ii] = ' ';
            
            // Get Indexes
            std::stringstream ss(line.c_str() + 2);
            int a, at, b, bt, c, ct, d, dt;
            ss >> a >> at >> b >> bt >> c >> ct >> d >> dt;

            // Append Triangles
            AddTriangle(
                { verts_palette[d - 1], verts_palette[c - 1], verts_palette[b - 1] },
                { uvs_palette[at - 1], uvs_palette[ct - 1], uvs_palette[bt - 1] });
            AddTriangle(
                { verts_palette[a - 1], verts_palette[d - 1], verts_palette[b - 1] },
                { uvs_palette[at - 1], uvs_palette[dt - 1], uvs_palette[ct - 1] });
        }
    }
}


// Add Face to Verts/Uvs
void UIPattern::AddTriangle(std::array<std::array<float,2>,3> _vts, std::array<std::array<float,2>,3> _uvs)
{
    for (int ii = 0; ii < 3; ++ii)
    {
        for (auto v : _vts[ii])
            verts.push_back(v);
        verts.push_back(-GH_NEAR_MAX);
    }
    for (int jj = 0; jj < 3; ++jj)
        for (auto u : _uvs[jj])
            uvs.push_back(u);
}