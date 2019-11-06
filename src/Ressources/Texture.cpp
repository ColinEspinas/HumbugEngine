#include "HumbugEngine/Ressources/Texture.h"
#include <fstream>
#include <cassert>

Texture::Texture(std::string fname, int rows, int cols)
  : Ressource("Texture", fname), m_cols(cols), m_rows(rows)
{
  //Check if this is a 3D texture
  assert(rows >= 1 && cols >= 1);
  m_is3D = (rows > 1 || cols > 1);

  this->_Load(fname);
}

void Texture::Use() {
  if (m_is3D) {
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_texId);
  } else {
    glBindTexture(GL_TEXTURE_2D, m_texId);
  }
}

void Texture::_Load(std::string _path)
{
  //Open the bitmap
  std::ifstream fin(std::string("assets/textures/") + _path.c_str(), std::ios::in | std::ios::binary);
  if (!fin) {
    m_texId = 0;
    return;
  }

  //Read the bitmap
  char input[54];
  fin.read(input, 54);
  const GLsizei width = *reinterpret_cast<int32_t*>(&input[18]);
  const GLsizei height = *reinterpret_cast<int32_t*>(&input[22]);
  assert(width % m_cols == 0);
  assert(height % m_rows == 0);
  const int block_w = width / m_cols;
  const int block_h = height / m_rows;
  uint8_t* img = new uint8_t[width * height * 3];
  for (int y = height; y--> 0;) {
    const int row = y / block_h;
    const int ty = y % block_h;
    for (int x = 0; x < width; x++) {
      const int col = x / block_w;
      const int tx = x % block_w;
      uint8_t* ptr = img + ((row*m_cols + col)*(block_w * block_h) + ty*block_w + tx)*3;
      fin.read(reinterpret_cast<char*>(ptr), 3);
    }
    const int padding = (width * 3) % 4;
    if (padding) {
      char junk[3];
      fin.read(junk, 4 - padding);
    }
  }

  //Load texture into video memory
  glGenTextures(1, &m_texId);
  if (m_is3D) {
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_texId);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_GENERATE_MIPMAP, GL_TRUE);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGB8, width/m_rows, height/m_cols, m_rows*m_cols, 0, GL_BGR, GL_UNSIGNED_BYTE, img);
  } else {
    glBindTexture(GL_TEXTURE_2D, m_texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, img);
  }

  //Clenup
  delete[] img;
}