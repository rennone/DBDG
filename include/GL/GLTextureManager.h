#ifndef DBDG_GL_TEXTURE_MANAGER_H
#define DBDG_GL_TEXTURE_MANAGER_H

#include "../Graphic.h"
#include "../Texture.h"
#include <string>

namespace DBDG
{
  class GLTextureManager : public TextureManager
  {
    class GLTexture : public Texture
    {
      unsigned char *image;
      unsigned int texId;
    public:
      GLTexture(const std::string &fileName);
      ~GLTexture();
      void load(const std::string &fileName);
      void bind()const;
      void unbind()const;
    };
    
  public:
    static GLTextureManager& getInstance()
    {
      static GLTextureManager instance;
      return instance;
    }
    Texture* newTexture(const std::string &file_name) const;
  private:
  GLTextureManager():TextureManager(){};
    GLTextureManager(const GLTextureManager &other);
    GLTextureManager& operator=(const GLTextureManager &other);
  };
}
#endif
