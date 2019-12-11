#include "HumbugEngine/UIQuad.h"

UIQuad::UIQuad(std::string _texName)
{
    shader = AquireShader("user_interface");
    texture = AquireTexture(_texName.c_str());

    // DEBUG: TEST VALUES //
    verts = std::vector<float> {
        0,0,-GH_NEAR_MAX,
        .1,.1,-GH_NEAR_MAX,
        0,.1,-GH_NEAR_MAX,

        .1,.1,-GH_NEAR_MAX,
        0,0,-GH_NEAR_MAX,
        .1,0,-GH_NEAR_MAX
    };
    uvs = std::vector<float> {
        0,0,
        1,1,
        0,1,

        1,1,
        0,0,
        1,0
    };
    std::cout<<verts.size()<<" "<<uvs.size()<<std::endl; //DBEUG
    // DEBUG //

    // Buffer Set
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(3, vbo);
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(verts[0]), verts.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }
    {
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(uvs[0]), uvs.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    }
}

UIQuad::~UIQuad()
{
    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(1, &vao);
}

void UIQuad::Draw(const Camera& cam, uint32_t curFBO)
{
    if (texture)
    {
        const Matrix4 P = cam.projection;
        //const Matrix4 P = cam.Matrix();

        //std::cout<<"Texture found !"<<std::endl; // DEBUG
        shader->Use();
        texture->Use();

        glUniformMatrix4fv(glGetUniformLocation(shader->GetProgId(), "projection"), 1, GL_TRUE, P.m);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)verts.size());
    }
}