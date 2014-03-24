#ifndef DBDG_UTIL_ASSIMP_MODEL_H
#define DBDG_UTIL_ASSIMP_MODEL_H

#include "../Model.h"
#include "../math/Vector4.hpp"
#include <array>
#include <vector>
#include <map>

struct aiScene;
struct aiNode;
struct aiMesh;

namespace DBDG
{
  class Texture;
  class GLModelManager;
  struct UV
  {
    float u, v;
  UV():u(0), v(0){}
    ~UV(){}
    void set(const float &_u, const float &_v)
    {
      this->u = _u;
      this->v = _v;
    }
  };

  //頂点情報
  struct Vertex
  {
    Vector4 position;
    Vector3 normal;  
    UV uv;
  };

  struct Material
  {
    std::string materialName;  //マテリアル名(あれば)
    Color4 diffuse;  //拡散色
    Color4 ambient;  //環境色
    Color4 emission; //発光色
    Color4 specular; //反射色
    float shininess;  //輝度
    Texture* texture;
  Material()
  :texture(nullptr)
    {
      diffuse.set(0.310000, 0.310000, 0.310000, 1.000000);
      ambient.set(0.160000,0.160000,0.160000, 1);
      specular.set(0.390000,0.390000,0.390000, 1);
      shininess = 2.0;   
    }
    
    void bindMaterial() const;
  };

  class Mesh
  {
  public:
    Mesh(aiMesh *mesh);
    void draw(const std::vector<Material> &materials) const;
  private:    
    unsigned int triBufferId;
    int triVertexCount;
    unsigned int materialIndex;
    bool hasTextureCoords;
    //3角形ポリゴンのみ(最初にReadFileするときに, aiProcess_Triangularを指定しているのでok)
    std::vector<Vertex> tri_buffer; 
  };

  class Node
  {
  public:
    Node( aiNode *node);
    void draw( const std::vector<Mesh> &meshes,
               const std::vector<Material> &materials) const;
  private:
    std::vector< Node > children;
    std::vector< unsigned int > mesh_indices;
    std::array<float, 16> matrix;
  };

  class AssimpModel : public Model
  {
    friend class GLModelManager;
  public:
    AssimpModel();
    void render() const;
    void renderWithAlpha(const float &alpha)  const;
    void renderWithColor3(const Color3 &color)const;
    void renderWithColor4(const Color4 &color)const;
    void load(const std::string&, const float&);
    void dispose();
  private:
    AssimpModel(const std::string &file_name, const float &scale);
    
    Node *root;
    std::vector<Material> materials;
    std::vector<Mesh> meshes;
    std::map<std::string, Texture*> textureHashtable;

    void loadMaterial(const aiScene *scene);
  };
}
#endif
