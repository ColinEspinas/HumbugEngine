#include "HumbugEngine/Mesh.h"
#include "HumbugEngine/Vector.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>

Mesh::Mesh(const char* fname) {
  //Open the file for reading
  std::ifstream fin(std::string("assets/meshes/") + fname);
  if (!fin) {
    return;
  }

  //Temporaries
  std::vector<float> vert_palette;
  std::vector<float> uv_palette;
  bool is3DTex = false;

  //Materials Related
  std::vector<std::string> material_name_palette;
  std::vector<Material> material_palette;
  std::string mtl_file;
  material_palette.push_back(Material("__Default"));

  int __countUp = 0; //DEBUG

  //Read the file
  std::string line;
  while (!fin.eof())
  {
	  std::getline(fin, line);
	  __countUp++; //DEBUG

	  // Create Vertices (Points)
	  if (line.find("v ") == 0)
	  {
		  std::stringstream ss(line.c_str() + 2);
		  float x, y, z;
		  ss >> x >> y >> z;
		  vert_palette.push_back(x);
		  vert_palette.push_back(y);
		  vert_palette.push_back(z);
	  }

	  // Create UV (Textures)
	  else if (line.find("vt ") == 0)
	  {
		  std::stringstream ss(line.c_str() + 2);
		  float x, y, z;
		  ss >> x >> y >> z;
		  uv_palette.push_back(x);
		  uv_palette.push_back(y);
		  if (!ss.fail())
		  {
			  uv_palette.push_back(z);
			  is3DTex = true;
		  }
	  }

	  // Create Collision
	  else if (line.find("c") == 0)
	  {
		  int a, b, c;
		  if (line[2] == '*')
		  {
			  const int v_ix = (int)vert_palette.size() / 3;
			  a = v_ix - 2; b = v_ix - 1; c = v_ix;
		  } else {
			  std::stringstream ss(line.c_str() + 2);
			  ss >> a >> b >> c;
		  }
		  const Vector3 v1(&vert_palette[(a - 1) * 3]);
		  const Vector3 v2(&vert_palette[(b - 1) * 3]);
		  const Vector3 v3(&vert_palette[(c - 1) * 3]);
		  colliders.push_back(Collider(v1, v2, v3));
	  }

	  // Create Faces
	  else if (line.find("f ") == 0)
	  {
		  // Simple Space Verification
		  if (*line.rbegin() == ' ')
			  line.pop_back();

		  // Count Slashes & Spaces
		  bool isDoubleSlash = false;
		  int n_slash = 0, n_space = 0;
		  for (size_t ii = 1; ii < line.size(); ii++)
		  {
			  if (line[ii] == '/')
			  {
				  if (line[ii + 1] == '/')
					  isDoubleSlash = true;
				  n_slash++;
				  line[ii] = ' ';
			  }
			  else if (line[ii] == ' ')
			  {
				  n_space++;
			  }
		  }

		  // Verify kCoeff Integrety
		  int kCoeff = n_slash / n_space;
		  switch (kCoeff)
		  {
		  case 0:
		  case 1:
		  case 2:
			  break;
		  default:
			  return;
		  }

		  // Append Vertex & Textures Indexes
		  line.push_back(' ');
		  line.push_back('0');
		  std::stringstream ss(line.c_str() + 2);
		  std::vector<int> iBuf, uBuf;
		  int tVal;
		  kCoeff += isDoubleSlash ? 0 : 1;
		  for (int aa = 0;; aa++)
		  {
			  ss >> tVal;

			  // Exit Loop
			  if (aa > kCoeff)
				  if (tVal == 0)
					  break;

			  // Append to Right Buffer
			  if (aa % kCoeff == 0)
				  iBuf.push_back(tVal);
			  else if (aa % kCoeff == 1)
				  uBuf.push_back(tVal);
		  }

		  // Add Faces
		  bool useTextures = (uBuf.size() != 0);
		  for (int ii = 0; ii < iBuf.size() - 2; ii++)
			  AddFace(vert_palette, uv_palette,
				  iBuf[0],			useTextures ? uBuf[0] : iBuf[0],				// a, at
				  iBuf[ii + 1],		useTextures ? uBuf[ii + 1] : iBuf[ii + 1],		// b, bt
				  iBuf[ii + 2],		useTextures ? uBuf[ii + 2] : iBuf[ii + 2],		// c, ct
				  is3DTex);
	  }

	//  // Materials
	//} else if (line.find("mtllib ") == 0) {
	//	isUsingMaterials = true;
	//	std::stringstream ss(line.c_str() + 7);
	//	ss >> mtl_file;
	//} else if (line.find("usemtl ") == 0 && isUsingMaterials) {
	//	std::string tname;
	//	std::stringstream ss(line.c_str() + 7);
	//	ss >> tname;
	//	material_name_palette.push_back(tname);
	//}
  }

  // Read .mtl File
  if (isUsingMaterials)
  {
	  std::ifstream fin2(std::string("Meshes/") + mtl_file);
	  if (fin2)
	  {
		  while (!fin2.eof())
		  {
			  std::getline(fin2, line);
			  if (line.find("newmtl ") == 0) {
				  std::string tname;
				  std::stringstream ss(line.c_str() + 7);
				  ss >> tname;
				  material_palette.push_back(Material(tname));
			  } else if (line.find("K") == 0) {
				  float x, y, z;
				  std::stringstream ss(line.c_str() + 3);
				  ss >> x >> y >> z;
				  if (line.find("a ") == 1)
					  material_palette.rbegin()->ambient = Vector3(x, y, z);
				  else if (line.find("d ") == 1)
					  material_palette.rbegin()->diffuse = Vector3(x, y, z);
				  else if (line.find("s ") == 1)
					  material_palette.rbegin()->specular = Vector3(x, y, z);
			  } else if (line.find("Ns ") == 0) {
				  float v;
				  std::stringstream ss(line.c_str() + 3);
				  ss >> v;
				  material_palette.rbegin()->shininess = v;
			  }
		  }

		  // Set Material
		  /// TODO
	  }
  }

  //for (auto S : material_name_palette) std::cout << S << std::endl; //DEBUG
  //for (auto M : material_palette) M.Print(); //DEBUG

  std::vector<float> color = { 1.0f,1.0f,1.0f };

  //Setup GL
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(NUM_VBOS, vbo);
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
    glVertexAttribPointer(1, (is3DTex ? 3 : 2), GL_FLOAT, GL_FALSE, 0, 0);
  }
  {
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), normals.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  }
  {
	  // TO MODIFY -----------------------------------------
	  glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	  glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(color[0]), color.data(), GL_STATIC_DRAW);
  }
}

Mesh::~Mesh() {
  glDeleteBuffers(NUM_VBOS, vbo);
  glDeleteVertexArrays(1, &vao);
}

void Mesh::Draw() {
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, (GLsizei)verts.size());
}

void Mesh::DebugDraw(const Camera& cam, const Matrix4& objMat) {
  for (size_t i = 0; i < colliders.size(); ++i) {
    colliders[i].DebugDraw(cam, objMat);
  }
}

void Mesh::AddFace(
  const std::vector<float>& vert_palette, const std::vector<float>& uv_palette,
  uint32_t a, uint32_t at, uint32_t b, uint32_t bt, uint32_t c, uint32_t ct, bool is3DTex)
{
  //Merge texture and vertex indicies
  assert(a > 0 && b > 0 && c > 0);
  assert(at > 0 && bt > 0 && ct > 0);
  a -= 1; b -= 1; c -= 1;
  at -= 1; bt -= 1; ct -= 1;
  const uint32_t v_ix[3] = { a, b, c };
  const uint32_t uv_ix[3] = { at, bt, ct };

  //Calcuate the normal for this face
  const Vector3 v1(&vert_palette[a * 3]);
  const Vector3 v2(&vert_palette[b * 3]);
  const Vector3 v3(&vert_palette[c * 3]);
  const Vector3 normal = (v2 - v1).Cross(v3 - v1).Normalized();

  for (int i = 0; i < 3; ++i) {
    const uint32_t v = v_ix[i];
    const uint32_t vt = uv_ix[i];
    assert(v < vert_palette.size() / 3);
    verts.push_back(vert_palette[v * 3]);
    verts.push_back(vert_palette[v * 3 + 1]);
    verts.push_back(vert_palette[v * 3 + 2]);
    if (!uv_palette.empty()) {
      if (is3DTex) {
        assert(vt < uv_palette.size() / 3);
        uvs.push_back(uv_palette[vt * 3]);
        uvs.push_back(uv_palette[vt * 3 + 1]);
        uvs.push_back(uv_palette[vt * 3 + 2]);
      } else {
        assert(vt < uv_palette.size() / 2);
        uvs.push_back(uv_palette[vt * 2]);
        uvs.push_back(uv_palette[vt * 2 + 1]);
      }
    } else {
      uvs.push_back(0.0f);
      uvs.push_back(0.0f);
    }
    normals.push_back(normal.x);
    normals.push_back(normal.y);
    normals.push_back(normal.z);
  }
}
