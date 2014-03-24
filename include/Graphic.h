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
    virtual Texture* newTexture(const std::string &file_name) const = 0;
  };
  
  class ModelManager
  {
  public:
    virtual ~ModelManager(){}
    virtual Model* newModel(const std::string &file_name, const float &scale) const = 0;
  };
  
  class Graphic
  {
  public:
    virtual TextureManager* const getTextureManager() const = 0;
    virtual ModelManager* const getModelManager() const = 0;
  };  
}

#endif

  
