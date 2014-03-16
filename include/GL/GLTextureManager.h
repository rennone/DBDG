#ifndef DBDG_GL_TEXTURE_MANAGER_H
#define DBDG_GL_TEXTURE_MANAGER_H

#include "../Graphic.h"
namespace DBDG
{
  class GLTextureManager : public TextureManager
  {
  public:
    static GLTextureManager* getInstance()
    {
      static GLTextureManager instance;
      return &instance;
    }
    Texture* newTexture(const std::string file_name);
  private:
    GLTextureManager(){}
    GLTextureManager(const GLTextureManager &other);
    GLTextureManager& operator=(const GLTextureManager &other);
  };
}
#endif