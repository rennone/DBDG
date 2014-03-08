#ifndef DBDG_FONT_H
#define DBDG_FONT_H

#include <Resource.h>
#include <math/Vector2.hpp>
#include<string>

namespace DBDG
{
  class Font
  {
  public:
    enum Alignment
    {
      ALIGNMENT_LEFT,
      ALIGNMENT_RIGHT,
      ALIGNMENT_CENTER,      
    };
    
    Font() { }
    ~Font() { }
  };
}
#endif
