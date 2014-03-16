#ifndef DBDG_GRAPHICS_H
#define DBDG_GRAPHICS_H

namespace DBDG
{
  class Texture;
  class Model;
  
  class TextureManager
  {
  public:
    virtual ~TextureManager(){}
    Texture* newTexture(const string &file_name);
  };
  
  class ModelManager
  {
  public:
    virutal ~ModelManager(){}
    Model* newModel(const string &file_name);
  };
  
  class Graphic
  {
  public:
    virtual TextureManager* const getTextureManager() const = 0;
    virtual ModelManager* const getModelManager() const = 0;
  };  
}

#endif

  
