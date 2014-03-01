#ifndef DBDG_TEXTURE_H
#define DBDG_TEXTURE_H

#include "Resource.h"
namespace DBDG
{
  class Texture : public Resource
  {
  protected:
    unsigned int width;  //pixel size (must be power of 2)
    unsigned int height;
  public:
  Texture(const std::string &file_name)
    :Resource(file_name)
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
  
  TextureRegion(const Texture *_texture,const float center_x,const float center_y,const float width,const float height)
    :texture(_texture),
      u1(        1.0*center_x/_texture->getWidth()), v1(          1.0*center_y/_texture->getHeight()),
      u2(1.0*(center_x+width)/_texture->getWidth()), v2( 1.0*(center_y+height)/_texture->getHeight()), ratio(width/height)
    { }

  TextureRegion(const Texture *_texture)
    :texture(_texture),
      u1(0), v1(0),
      u2(1), v2(1), ratio(_texture->getWidth()/(float)texture->getHeight())
    { }
  };
}

#endif
