#include <GL/glDBDG.h>
#include <Texture.h>
#include <GL/AssimpModel.h>
#include <GL/assimp/Importer.hpp>
#include <GL/assimp/scene.h>
#include <GL/assimp/mesh.h>
#include <GL/assimp/postprocess.h>

#include <iostream> //DEBUG

namespace DBDG
{
  void Material::bindMaterial() const
  {
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT , (const GLfloat*)&ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE , (const GLfloat*)&diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (const GLfloat*)&specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shininess);

    if(texture != nullptr)    
      texture->bind();    
  }

  Mesh::Mesh(aiMesh *mesh)
  {
    materialIndex = mesh->mMaterialIndex;
    hasTextureCoords = mesh->HasTextureCoords(0); // ? what means 0 ?
    
    //すべてのポリゴン(face)から頂点を抽出
    for(int current_face = 0; current_face < mesh->mNumFaces; current_face++)
    {
      const aiFace *face = &mesh->mFaces[current_face];
      //全部3角形なので, tri_bufferに入れる
      for(int i = 0; i < face->mNumIndices; i++)
      {
        Vertex vertex;
        const aiVector3D &position = mesh->mVertices[face->mIndices[i]];
        vertex.position.set(position.x, position.y, position.z, 1.0f);

        if(hasTextureCoords) {
          // mTextureCoordsの型は aiVector3D** なので左辺はポインタ 
          const aiVector3D *texcoord = mesh->mTextureCoords[0] + face->mIndices[i];
          vertex.uv.set(texcoord->x, texcoord->y);
        }
        const aiVector3D &normal = mesh->mNormals[face->mIndices[i]];
        vertex.normal.set(normal.x, normal.y, normal.z);
        
        tri_buffer.push_back(vertex);
      }
    }
    
    //バッファの生成
    glGenBuffers( 1, &triBufferId);
    glBindBuffer( GL_ARRAY_BUFFER, triBufferId);
    glBufferData(GL_ARRAY_BUFFER,
                 tri_buffer.size()*sizeof(Vertex),
                 reinterpret_cast<void*>(tri_buffer.data()), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    triVertexCount = tri_buffer.size();
  }

  void Mesh::draw(const std::vector<Material> &materials) const
  {
    materials[materialIndex].bindMaterial();
    //３角形描画
    glBindBuffer( GL_ARRAY_BUFFER, triBufferId);

    glVertexPointer(3, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(0));
    glNormalPointer(GL_FLOAT, sizeof(Vertex),
                    reinterpret_cast<void*>( sizeof(Vector4) ));
    
    if(hasTextureCoords)
    {
      glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), reinterpret_cast<void*>(sizeof(Vector4) + sizeof(Vector3) ));
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    else
    {
      glDisable(GL_TEXTURE_2D);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
    
    glDrawArrays( GL_TRIANGLES, 0, triVertexCount);
  }  

  Node::Node( aiNode* node)
  {
    children.reserve(node->mNumChildren);
    for( int i_child = 0; i_child != node->mNumChildren; i_child++) {
      children.push_back( Node(node->mChildren[i_child] ) );      
    }
    
    for( int i_elem = 0; i_elem != 16; i_elem++ ){
      matrix[i_elem] = node->mTransformation[i_elem%4][i_elem/4];      
    }

    mesh_indices.reserve( node->mNumMeshes );
    for( int i_elem = 0; i_elem != node->mNumMeshes; i_elem++)
    {
      mesh_indices.push_back( node->mMeshes[i_elem]);
    }
  }

  void Node::draw( const std::vector<Mesh> &meshes, const std::vector<Material> &materials) const
  {
    glPushMatrix();
    glMultMatrixf( matrix.data() );
    for( const Node &child : children){
      child.draw(meshes, materials);
    }

    for( const int &index : mesh_indices){
      meshes[index].draw(materials);
    }
    glPopMatrix();
  }
  
  AssimpModel::AssimpModel(const std::string &file_name, const float &scale)
    :Model(file_name)
  {
    load(file_name, scale);
  }

  void AssimpModel::loadMaterial(const aiScene *scene)
  {    
    //マテリアルとテクスチャを読み込む
    materials.reserve(scene->mNumMaterials);    
    for(int i=0; i<scene->mNumMaterials; i++) {      
      aiString path_from_here;
      Material mat;
      float alpha = 1.0f; //透明度の情報が入ってない場合は,更新されないのでデフォルトを1にしておく
      scene->mMaterials[i]->Get(AI_MATKEY_OPACITY, alpha);

      aiColor3D color(0.0f, 0.0f, 0.0f);
      scene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
      mat.diffuse.set(color.r, color.g, color.b, alpha);
      
      scene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, color);
      mat.ambient.set(color.r, color.g, color.b, alpha);
      
      scene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, color);
      mat.specular.set(color.r, color.g, color.b, alpha);

      float shininess;
      scene->mMaterials[i]->Get(AI_MATKEY_SHININESS, shininess);
      mat.shininess = shininess;

      if(scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &path_from_here,
                                          NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
      {
        std::string path_str = path_from_here.C_Str();
        if(textureHashtable.count(path_str) == 0) {
          textureHashtable.insert(
            {path_str
                ,GLGraphic::getInstance()->getTextureManager()->newTexture( Model::superiorPath + path_str)});
        }
        mat.texture = textureHashtable.at(path_str);
      }
      materials.push_back(std::move(mat));
    }
  }

  void AssimpModel::load(const std::string &full_path_name, const float &scale)
  {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(full_path_name, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    root = new Node(scene->mRootNode);
    
    meshes.reserve( scene->mNumMeshes);
    for(int i = 0; i < scene->mNumMeshes; i++) {
      meshes.push_back( Mesh(scene->mMeshes[i]) );
    }

    loadMaterial(scene);

    //ここで delete sceneをしたら, 落ちたので
    //sceneはImporterのデストラクタで破壊されると思う...
  }
  
  void AssimpModel::render() const
  {
    glPushAttrib( GL_COLOR_MATERIAL   | GL_CURRENT_BIT | GL_ENABLE_BIT |
                  GL_COLOR_BUFFER_BIT | GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST); //アルファテスト開始
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    root->draw(meshes, materials);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopAttrib();  
  }

  void AssimpModel::renderWithAlpha(const float &alpha)  const
  {
    render();
  }
  void AssimpModel::renderWithColor3(const Color3 &color)const
  {
    render();
  }
  void AssimpModel::renderWithColor4(const Color4 &color)const
  {
    render();
  }

  void AssimpModel::dispose()
  {
  }
    
}
