#ifndef DBDG_TEXTURE_H
#define DBDG_TEXTURE_H

#include <string>
namespace DBDG
{
  class Texture
  {
  protected:
    std::string fileName;
    unsigned int width;  //pixel size (must be power of 2)
    unsigned int height;
  public:
  Texture(const std::string &file_name)
    :fileName(file_name)
    { }
    
    virtual ~Texture(){ }
  
    virtual void load(const std::string &file_name) = 0;
    virtual void bind()   const = 0;
    virtual void unbind() const = 0;
    unsigned getWidth()  const  {  return width;  }  
    unsigned getHeight() const  {  return height; }
  };

  class TextureRegion
  {
  public:
    const Texture *texture;
    const float u1, v1;
    const float u2, v2;
    const float ratio; // width/height;
  
  TextureRegion(const Texture *_texture,const float left,const float top,const float width,const float height)
    :texture(_texture),
      u1(        1.0*left/_texture->getWidth()), v1(          1.0*top/_texture->getHeight()),
      u2(1.0*(left+width)/_texture->getWidth()), v2( 1.0*(top+height)/_texture->getHeight()), ratio(width/height)
    { }

  TextureRegion(const Texture *_texture)
    :texture(_texture),
      u1(0), v1(0),
      u2(1), v2(1), ratio(_texture->getWidth()/(float)texture->getHeight())
    { }
  };
}

#endif
