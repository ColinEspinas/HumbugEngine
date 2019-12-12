#pragma once
#include "HumbugEngine/Shader.h"
#include "HumbugEngine/Texture.h"
#include "HumbugEngine/Resources.h"
#include "HumbugEngine/GameHeader.h"
#include <GL/glew.h>


class UIQuad
{
public:
    UIQuad(std::string _texName);
    ~UIQuad();

    void Draw(const Camera& cam, uint32_t curFBO);

    std::shared_ptr<Texture> texture;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<UIPattern> pattern;

private:
    std::vector<float> verts;
    std::vector<float> uvs;

    GLuint vao;
    GLuint vbo[2];
};
typedef std::vector<std::shared_ptr<UIQuad>> PQuadVec;