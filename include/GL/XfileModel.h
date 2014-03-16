#ifndef DBDG_X_FILE_MODEL_H
#define DBDG_X_FILE_MODEL_H

#include <vector>
#include <string>
#include <map>

#include "../Model.h"
#include "../math/Vector3.hpp"
#include "../Color4.hpp"
#include "../Color3.hpp"

namespace DBDG
{
  class Texture;
  
  class XfileModel : public Model
  {
    class UV
    {
    public:
      float u, v;
    };    

    class Mesh
    {
    public:
      Vector3 vertex;
      Vector3 normal;
      UV uv;
    };
  
    class Material
    {
    public:
      std::string materialName;  //�}�e���A����(�����)
      Color4 diffuse;  //�g�U�F
      Color4 ambient;  //���F
      Color4 emission; //�����F
      Color4 specular; //���ːF
      float shininess;  //�P�x    
      Texture *texture;
      unsigned int bufferId; //VBO�o�b�t�@ID�i�[�p
      std::vector <Mesh> meshes;//�O�p�ʃf�[�^
    Material():texture(NULL){ }    
    };

  public:
    XfileModel(const std::string&, const float&);
    ~XfileModel();  
    virtual void load(const std::string &file_name, const float &size);
    
    virtual void render() const;    
    virtual void renderWithAlpha(const float &alpha) const;
    virtual void renderWithColor3(const Color3 &color) const;
    virtual void renderWithColor4(const Color4 &color) const;
    virtual void dispose();

  private:
    std::vector <Material> materials;
    std::map<std::string, Texture*> textureList; //�e�N�X�`��       
  
    void readMaterial(FILE *fp);
    void readMesh(FILE *fp, std::vector<Vector3> &vertices, std::vector<int> &indexis, const float &size);
    void readMeshNormal(FILE *fp, std::vector<Vector3> &normal, std::vector<int> &indexis);
    void readTexCoord(FILE *fp, std::vector<UV> &uv);
    void readMeshMaterialList(FILE *fp, std::vector<int> &indexis);

    void bindVBO(const unsigned int bufferId, const Texture *texture) const;
  };
}

#endif
