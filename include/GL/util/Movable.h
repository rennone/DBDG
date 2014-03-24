#ifndef DBDG_GL_UTIL_CHARACTER_H
#define DBDG_GL_UTIL_CHARACTER_H

#include "HasPosition.h"

namespace DBDG
{
  namespace Util
  {
    class Movable : public HasPosition
    {
    protected:
      Vector3 direction;
    public:
      Movable(GLGame *glGame, const Vector3 &position, const Vector3 &direction)
        :HasPosition(glGame, position)
        ,direction(direction)
      {
      }
      
      Movable(GLGame *glGame)
        :HasPosition(glGame)
        ,direction(Vector3())
      {
      }
      
      virtual ~Movable(){}

      Vector3 getDirection() const { return direction; }
      void setDirection(const Vector3 &direction) { this->direction = direction; }
    };
  }
}

#endif
