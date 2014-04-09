#include <GL/glDBDG.h>
#include <GL/XfileModel.h>
#include <Color4.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <Resource.h>
#include <FileIO.h>

namespace
{    
  std::string spliter(std::string str) 
  {
    int p = 0; 
    std::string res;

    while(str[p] != '\"') { p++; }
    p++;

    while(str[p] != '\"') { res += str[p]; p++; }

    return res;
  }

  void skipBrackets(FILE *fp)
  {
    char buf[255];
    // '}'がくるまで飛ばす
    while(strchr(buf,'}')==NULL)
      fgets(buf,sizeof(buf),fp);

    fgets(buf,sizeof(buf),fp);
  }
}

namespace DBDG
{
  XfileModel::XfileModel(const std::string &fileName)
    :Model(fileName)
  {
    load(fileName);
  }

  XfileModel::~XfileModel()
  {
    dispose();
  }
  
//マテリアルの読み込み
  void XfileModel::readMaterial(FILE *fp)
  {
    Material mtl;
    char buf[255];
    fgets(buf,sizeof(buf),fp);//改行する(次の行からデータがあると仮定)
    Color4 color;
    int err;
    //ディフューズ
    err = fscanf(fp,"%f;%f;%f;%f;;",&color.r,&color.g,&color.b,&color.a);
//  mtl.materialColor.diffuse = color;
    mtl.diffuse = color;
    //SHININESS  
    err = fscanf(fp,"%f;",&mtl.shininess);

    //残りはアルファ値はないのでとりあえず1にしとく
    color.a = 1;
    //スペキュラー 
    err = fscanf(fp,"%f;%f;%f;;",&color.r, &color.g, &color.b);
    mtl.specular=color;
  
    //エミッシブ
    err = fscanf(fp,"%f;%f;%f;;",&color.r, &color.g, &color.b);  
    mtl.ambient=color;

    char key[255];
    //テクスチャー
    err = fscanf(fp,"%s ",key);

    mtl.texture = NULL;      
    if(strcmp(key,"TextureFilename")==0)
    {
      fgets(buf,sizeof(buf),fp);//直後の行にあると推定　改行する
      err = fscanf(fp,"%s",buf); //テクスチャネーム
    
      std::string texName = buf;
      texName = spliter(texName);

      //textureListに無ければ追加
      if(textureList.find(texName) == textureList.end())
        textureList[texName] = GLGraphic::getInstance().getTextureManager().newTexture(Model::superiorPath + texName);

      mtl.texture = textureList[texName];
    }
  
    materials.push_back(mtl);
  }

//メッシュ情報の読み込み
  void XfileModel::readMesh(FILE *fp, std::vector<Vector3> &vertices, std::vector<int> &indexis)
  {
    char buf[255];
    int err;
    fgets(buf,sizeof(buf),fp);  //改行する
    fgets(buf,sizeof(buf),fp);  //頂点の数を取得
  
    int vertexNum = atoi(buf);
  
    vertices.reserve(vertexNum);
    //メッシュの数だけ読み込む
    for(int i=0;i<vertexNum ;i++)
    {
      Vector3 vec;
      err = fscanf(fp,"%f;%f;%f;,",&vec.x,&vec.y,&vec.z);
      vertices.push_back(vec);
    }
  
    //頂点インデックス読み込み  
    fgets(buf,sizeof(buf),fp); //次の行へ
    //メッシュの数が取得できるまで, 空行をとばす
    fgets(buf,sizeof(buf),fp);
    while(strchr(buf,';')==NULL)
      fgets(buf,sizeof(buf),fp);
  
    int meshNum = atoi(buf);
    indexis.reserve(meshNum);
    for(int i=0;i<meshNum ;i++)
    {
      int v1,v2,v3,v4;
      int vecNum; //メッシュの頂点数
      err = fscanf(fp,"%d;",&vecNum);
      indexis.push_back(vecNum);
      if(vecNum == 3)
      {
        fscanf(fp,"%d,%d,%d;,",&v1,&v2,&v3);
        indexis.push_back(v1);
        indexis.push_back(v2);
        indexis.push_back(v3);
      }
      else
      {
        err = fscanf(fp,"%d,%d,%d,%d;,",&v1,&v2,&v3,&v4);
        indexis.push_back(v1);
        indexis.push_back(v2);
        indexis.push_back(v3);
        indexis.push_back(v4);
      }
    }
  }

  void XfileModel::readMeshNormal(FILE *fp, std::vector<Vector3> &normal, std::vector<int> &indexis)
  {
    char buf[255];
    //法線データの読み込み
    fgets(buf,sizeof(buf),fp); //改行する
    fgets(buf,sizeof(buf),fp); //法線の数を取得
    int normalNum=atoi(buf);
    int err;
    normal.reserve(normalNum);
  
    for(int i=0;i<normalNum ;i++)
    {
      Vector3 vec;
      err = fscanf(fp,"%f;%f;%f;,",&vec.x, &vec.y, &vec.z);
      normal.push_back(vec);
    }
  
    //法線インデックス(どのポリゴンがどの頂点を使っているか)を読み込み  
    fgets(buf,sizeof(buf),fp);//データは2行下にあると推定　改行する
    fgets(buf,sizeof(buf),fp);
    while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//空行対策
    int meshNum=atoi(buf);
    indexis.reserve(meshNum);
    for(int i=0;i<meshNum ;i++)
    {
      int norNum;
      int v1,v2,v3,v4;
      err = fscanf(fp,"%d;",&norNum);
      indexis.push_back(norNum);
      if(norNum == 3)
      {      
        fscanf(fp,"%d,%d,%d;,",&v1,&v2,&v3);
        indexis.push_back(v1);
        indexis.push_back(v2);
        indexis.push_back(v3);
      }
      else
      {
        err = fscanf(fp,"%d,%d,%d,%d;,",&v1,&v2,&v3,&v4);
        indexis.push_back(v1);
        indexis.push_back(v2);
        indexis.push_back(v3);
        indexis.push_back(v4);
      }
    }
  }

  void XfileModel::readTexCoord(FILE *fp, std::vector<UV> &uv)
  {
    char buf[255];
    int err;
    fgets(buf,sizeof(buf),fp);//データは2行下にあると推定　改行する
    fgets(buf,sizeof(buf),fp);
    while(strchr(buf,';')==NULL){fgets(buf,sizeof(buf),fp);}//空行対策
    int texNum=atoi(buf);
    uv.reserve(texNum);
    for(int i=0;i<texNum ;i++)
    {
      UV vec;
      err = fscanf(fp,"%f;%f;,",&vec.u,&vec.v);
      uv.push_back(vec);
    }
  }

  void XfileModel::readMeshMaterialList(FILE *fp, std::vector<int> &indexis)
  {
    char buf[255]; 
    fgets(buf,sizeof(buf),fp);//空改行
    fgets(buf,sizeof(buf),fp);//マテリアル数
    fgets(buf,sizeof(buf),fp);//リスト要素数
    int meshNum=atoi(buf);
    for(int i=0;i<meshNum;i++)
    {
      fgets(buf,sizeof(buf),fp);
      int index=atoi(buf);
      indexis.push_back(index);
    }
  }

  void XfileModel::load(const std::string &fileName)
  {
    Material mtl;
    std::vector <Vector3> Vertex;//頂点
    std::vector <Vector3> Normal;//法線
    std::vector <UV> uv;//UV
    std::vector <int> VertexIndex;
    std::vector <int> NormalIndex;
    std::vector <int> MaterialIndex;
    int err;
    char key[255];
    //Xファイルを開いて内容を読み込む
    FILE* fp=NULL;

    fp = FileIO::getInstance().fileOpen(fileName, "rt");
    //読み込み 
    fseek(fp,SEEK_SET,0);
    while(!feof(fp))
    {
      //キーワード 読み込み
      memset(key, 0, sizeof(key));
      err = fscanf(fp,"%s ",key);

      //テンプレートの行は跳ばす
      if(strcmp(key, "template") == 0)    
        skipBrackets(fp);    
    
      if(strcmp(key,"Material")==0)    
        readMaterial(fp);  //マテリアルを読み込む    
    
      //頂点 読み込み
      if(strcmp(key,"Mesh")==0)    
        readMesh(fp, Vertex, VertexIndex);
    
      //法線 読み込み
      if(strcmp(key,"MeshNormals")==0)    
        readMeshNormal(fp, Normal, NormalIndex);
    
      //テクスチャー座標 読み込み
      if(strcmp(key,"MeshTextureCoords")==0)    
        readTexCoord(fp, uv);
        
      //マテリアルリスト
      if(strcmp(key,"MeshMaterialList")==0)    
        readMeshMaterialList(fp, MaterialIndex);    
    }  
    fclose(fp);

    int j = 0;//0番目のポリゴンの頂点数が格納されている添字
    for( auto mtlIndex : MaterialIndex )
    {
      Mesh mesh;
      if ( VertexIndex[j] == 3)
      {
        for( int k=1; k<=3; k++)
        {
          Mesh mesh;
          mesh.vertex=Vertex[VertexIndex[j+k]];
          mesh.normal=Normal[NormalIndex[j+k]];
          mesh.uv=uv[VertexIndex[j+k]];        
          materials[mtlIndex].meshes.push_back(mesh);
        }
        j+=4; //次のポリゴンの頂点数が格納されている添字
      }
      else
      {
        //4角形ポリゴンは3角形に分離して格納
        //todo 向きによっては, 法線が逆になるので, 計算する必要あり.
        int index[] = {1, 2, 3, 1, 3, 4};
        for( int k=0; k<6; k++)
        {
          Mesh mesh;
          mesh.vertex=Vertex[VertexIndex[j+index[k]]];
          mesh.normal=Normal[NormalIndex[j+index[k]]];
          mesh.uv=uv[VertexIndex[j+index[k]]];
          materials[mtlIndex].meshes.push_back(mesh);
        }
        j+=5;//次のポリゴンの頂点数が格納されている添字
      }
    }

//VBO化して,GPUに置いておく
    for ( int i=0; i<materials.size(); i++)
    {
      glGenBuffers(1, &materials[i].bufferId);
      glBindBuffer(GL_ARRAY_BUFFER, materials[i].bufferId);
      glBufferData(GL_ARRAY_BUFFER, materials[i].meshes.size()*sizeof(Mesh), (GLfloat*)&materials[i].meshes[0], GL_STATIC_DRAW);    
      glBindBuffer(GL_ARRAY_BUFFER, 0); 
    }

    return;
  }

  inline static void setMaterialColor(const Color4 &ambient, const Color4 &diffuse, const Color4 &specular, const float &shininess)
  {
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT , (const GLfloat*)&ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE , (const GLfloat*)&diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, (const GLfloat*)&specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shininess);
  }

  inline static void setMaterialColor(Color4 ambient, Color4 diffuse, Color4 specular, const float &shininess, const float &alpha)
  {
    ambient.a = diffuse.a = specular.a = alpha;
    setMaterialColor(ambient, diffuse, specular, shininess);
  }

  inline static void beginRender()
  {
    glPushAttrib( GL_COLOR_MATERIAL   | GL_CURRENT_BIT | GL_ENABLE_BIT |
                  GL_COLOR_BUFFER_BIT | GL_TEXTURE_BIT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST); //アルファテスト開始
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
  }

  inline static void endRender()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glPopAttrib();  
  }

  #define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
  
  inline void XfileModel::bindVBO(const unsigned int bufferId, const Texture *texture) const
  {
    //VBO使うタイプ
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glVertexPointer(3, GL_FLOAT, sizeof(Mesh), BUFFER_OFFSET(0));
    glNormalPointer(GL_FLOAT,sizeof(Mesh), BUFFER_OFFSET(sizeof(Vector3)));

    //テクスチャの設定
    if(texture != NULL)
    {
      texture->bind();
      glTexCoordPointer(2, GL_FLOAT, sizeof(Mesh), BUFFER_OFFSET(sizeof(Vector3)+sizeof(Vector3)));        
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);    
    }
    else
    {
      glDisable(GL_TEXTURE_2D);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }
  }
  
  void XfileModel::render() const
  {
    beginRender();    
    for(auto mat : materials)
    {
      //もしかしたら, 何のポリゴンも持たないマテリアルがあるかもしれないので, それ対策
      if ( mat.meshes.size() <= 0 )
        continue;

      setMaterialColor(mat.ambient, mat.diffuse, mat.specular, mat.shininess);

      bindVBO(mat.bufferId, mat.texture);
      
      glDrawArrays(GL_TRIANGLES, 0, mat.meshes.size());
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);    
    }
    endRender();    
  }
  
//描画
  void XfileModel::renderWithAlpha(const float &alpha) const
  {
    beginRender();
    
    for(auto &mat : materials)
    {
      //もしかしたら, 何のポリゴンも持たないマテリアルがあるかもしれないので, それ対策
      if ( mat.meshes.size() <= 0 )
        continue;

      setMaterialColor(mat.ambient, mat.diffuse, mat.specular, mat.shininess, alpha);

      bindVBO(mat.bufferId, mat.texture);
      
      glDrawArrays(GL_TRIANGLES, 0, mat.meshes.size());
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);    
    }
    endRender();
  }

  void XfileModel::renderWithColor4(const Color4 &color) const
  {
  beginRender();  
  
  for(auto &mat : materials)
  {
  //もしかしたら, 何のポリゴンも持たないマテリアルがあるかもしれないので, それ対策
  if ( mat.meshes.size() <= 0 )
    continue;

  setMaterialColor(color, color, color, mat.shininess);
//  setMaterialColor(mat.ambient+color, mat.diffuse+color, mat.specular+color, mat.shininess);

  bindVBO(mat.bufferId, mat.texture);
  glDrawArrays(GL_TRIANGLES, 0, mat.meshes.size());
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);    
}
  endRender();
  }
  
  void XfileModel::renderWithColor3(const Color3 &color3) const
  {
  beginRender();  

  const Color4 color(color3.r, color3.g, color3.b, 1);
  for(auto &mat : materials)
  {
  //もしかしたら, 何のポリゴンも持たないマテリアルがあるかもしれないので, それ対策
  if ( mat.meshes.size() <= 0 )
    continue;

  setMaterialColor(color, color, color, mat.shininess);

  bindVBO(mat.bufferId, mat.texture);
  glDrawArrays(GL_TRIANGLES, 0, mat.meshes.size());
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);    
}
  endRender();
  }
  
  void XfileModel::dispose()
  {
    for (unsigned int i=0; i<materials.size(); i++ )
    {
      //glDeleteBuffers(1, &materials[i].bufferId); //VBO使うタイプ
      materials[i].meshes.clear();
    }
    materials.clear();
  }
}

/*       
      //VBO使うタイプ
      glBindBuffer(GL_ARRAY_BUFFER, mat.bufferId);
      glVertexPointer(3, GL_FLOAT, sizeof(Mesh), BUFFER_OFFSET(0));
      glNormalPointer(GL_FLOAT,sizeof(Mesh), BUFFER_OFFSET(sizeof(Vector3)));
      
      //VBO使わないタイプ
      glVertexPointer(3, GL_FLOAT, sizeof(Mesh), (GLfloat*)&mat.meshes[0].vertex.x);
      glNormalPointer(GL_FLOAT,sizeof(Mesh), (GLfloat*)&mat.meshes[0].normal.x);
    
      //テクスチャの設定
      if(mat.texture != NULL)
      {
        mat.texture->bind();

        //VBO使うタイプ
        //glTexCoordPointer(2, GL_FLOAT, sizeof(Mesh), BUFFER_OFFSET(sizeof(Vector3)+sizeof(Vector3)));
        //VBO使わないタイプ
        glTexCoordPointer(2, GL_FLOAT, sizeof(Mesh), (GLfloat*)&mat.meshes[0].uv.u);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);    
      }
      else
      {
        glDisable(GL_TEXTURE_2D);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      }
    
*/
