#ifndef DBDG_FONT_H
#define DBDG_FONT_H

#include <Resource.h>
#include <math/Vector2.hpp>
#include<string>

namespace DBDG
{
  class Font : public Resource
  {
  protected:
    std::string fileName;
    virtual void load(std::string file_name) = 0;
  
  public:
  Font(std::string file_name)
    :Resource(file_name)
    {
      
    }
    ~Font() { }      
    virtual void drawString(const Vector2 &point, std::string str) const = 0;
  };
}
#endif
