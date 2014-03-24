#ifndef DBDG_GL_TEXTURE_H
#define DBDG_GL_TEXTURE_H

#include "../Texture.h"
//¡‚ÌŠ.pngƒIƒ“ƒŠ[
namespace DBDG
{
  class GLTextureManager;
  class GLTexture:public DBDG::Texture
  {
    friend class GLTextureManager;
    unsigned char *image;
    unsigned int texId;
    GLTexture(const std::string &fileName);
  public:
    ~GLTexture();
    void load(const std::string &fileName);
    void bind()const;
    void unbind()const;
  };
}

#endif
