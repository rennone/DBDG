#ifndef DBDG_GRAPHICS_H
#define DBDG_GRAPHICS_H

#include <string>

namespace DBDG
{
  class Texture;
  class Model;
  
  class TextureManager
  {
    TextureManager(const TextureManager&);
    TextureManager& operator=(const TextureManager&);
  public:
    TextureManager(){}
    virtual ~TextureManager(){}
    virtual Texture* newTexture(const std::string &file_name) const = 0;
  };
  
  class ModelManager
  {
    ModelManager(const ModelManager&);
    ModelManager& operator=(const ModelManager&);
  public:
    ModelManager(){}
    virtual ~ModelManager(){}
    virtual Model* newModel(const std::string &file_name) const = 0;
  };
  
  class Graphic
  {
    Graphic(const Graphic &);
    Graphic& operator=(const Graphic &);
  public:
    Graphic(){}
    virtual const TextureManager& getTextureManager() const = 0;
    virtual const ModelManager&   getModelManager()   const = 0;
  };  
}

#endif

  
