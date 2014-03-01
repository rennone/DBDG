#ifndef DBDG_MODEL_H
#define DBDG_MODEL_H

#include "Resource.h"
#include "Texture.h"
#include "Color3.hpp"
#include "Color4.hpp"
#include <string>

namespace DBDG
{
  class Model: public Resource
  {
  protected:
    Texture *texture;
    
  public:
  Model(const std::string &file_name)
    :Resource(file_name){  }
    virtual ~Model(){  }  
    virtual void render() const = 0;
    virtual void renderWithAlpha(const float &alpha) const = 0;
    virtual void renderWithColor3(const Color3 &color) const = 0;
    virtual void renderWithColor4(const Color4 &color) const = 0;
    virtual void load(const std::string&, const float&) = 0;
    virtual void dispose() = 0;
  };
}
#endif
