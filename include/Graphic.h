#ifndef DBDG_GRAPHICS_H
#define DBDG_GRAPHICS_H

#include <string>

namespace DBDG
{
  class Texture;
  class Model;
  
  class TextureManager
  {
  public:
    virtual ~TextureManager(){}
    Texture* newTexture(const std::string &file_name);
  };
  
  class ModelManager
  {
  public:
    virtual ~ModelManager(){}
    Model* newModel(const std::string &file_name, const float &scale);
  };
  
  class Graphic
  {
  public:
    virtual TextureManager* const getTextureManager() const = 0;
    virtual ModelManager* const getModelManager() const = 0;
  };  
}

#endif

  
