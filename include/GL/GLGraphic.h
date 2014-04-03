#ifndef DBDG_GL_GRAPHICS_H
#define DBDG_GL_GRAPHICS_H

#include "../Graphic.h"
#include "GLTextureManager.h"
#include "GLModelManager.h"

namespace DBDG
{
  class GLGraphic : public Graphic
  {
  public:
    static GLGraphic& getInstance()
    {
      static GLGraphic instance;
      return instance;
    }
  GLGraphic():Graphic(){}
    TextureManager& getTextureManager() const
    {
      return GLTextureManager::getInstance();
    }
    
    ModelManager& getModelManager() const
    {
      return GLModelManager::getInstance();
    }    
  private:
    GLGraphic(const GLGraphic &other);
    GLGraphic& operator=(const GLGraphic &other);
  };
}
#endif
