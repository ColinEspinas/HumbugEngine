#include "HumbugEngine/UIQuad.h"

UIQuad::UIQuad(std::string _uiName)
{
    pattern = AquirePattern(_uiName.c_str());
    shader = AquireShader("user_interface");

    if (pattern != nullptr)
    {
        texture = AquireTexture(pattern->texName.c_str());

        verts = pattern->verts;
        uvs = pattern->uvs;
    }

    //DEBUG//
    for (float v : verts) std::cout << std::to_string(v) << " "; std::cout << std::endl;
    for (float u : uvs) std::cout << std::to_string(u) << " "; std::cout << std::endl;
    std::cout << pattern->texName << " | str Size: " << pattern->texName.size() << std::endl;
    std::cout << (pattern == nullptr) << " | " << (texture == nullptr) << std::endl;
    //DEBUG//

    // DEBUG: TEST VALUES //
    // verts = std::vector<float> {
    //     0,0,-GH_NEAR_MAX,
    //     .1,.05,-GH_NEAR_MAX,
    //     0,.05,-GH_NEAR_MAX,

    //     .1,.05,-GH_NEAR_MAX,
    //     0,0,-GH_NEAR_MAX,
    //     .1,0,-GH_NEAR_MAX
    // };
    // uvs = std::vector<float> {
    //     0,0,
    //     1,1,
    //     0,1,

    //     1,1,
    //     0,0,
    //     1,0
    // };
    // std::cout<<verts.size()<<" "<<uvs.size()<<std::endl; //DBEUG
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

        Matrix4 localScale;
        float MaxDim = GH_MAX<float>(GH_SCREEN_WIDTH, GH_SCREEN_HEIGHT);
        localScale.MakeScale(Vector3(GH_NEAR_MAX * (GH_SCREEN_WIDTH + GH_SCREEN_X) / MaxDim,
             GH_NEAR_MAX * (GH_SCREEN_HEIGHT + GH_SCREEN_Y) / MaxDim, 1));

        //std::cout<<"Texture found !"<<std::endl; // DEBUG
        shader->Use();
        texture->Use();

        glUniformMatrix4fv(glGetUniformLocation(shader->GetProgId(), "u_Projection"), 1, GL_TRUE, P.m);
        glUniformMatrix4fv(glGetUniformLocation(shader->GetProgId(), "u_Scale"), 1, GL_TRUE, localScale.m);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei)verts.size());
    }
}