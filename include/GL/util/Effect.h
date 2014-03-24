#ifndef DBDG_GL_UTIL_EFFECT_H
#define DBDG_GL_UTIL_EFFECT_H

#include "Movable.h"
#include "../../SpriteAnimation.h"

namespace DBDG
{
  namespace Util
  {
    class Effect : public Movable
    {
      SpriteAnimation* effectAnimation;
    public:
      Effect(GLGame *glGame)
        :Movable(glGame)
      {        
      }
      virtual ~Effect(){}
    };
  }
}

#endif
