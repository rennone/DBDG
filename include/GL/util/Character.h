#ifndef DBDG_GL_UTIL_CHARACTER_H
#define DBDG_GL_UTIL_CHARACTER_H

#include "HasPosition.h"

namespace DBDG
{
  namespace Util
  {
    class Character : public HasPosition
    {
    protected:
      Vector3 direction;
    public:
      Character(GLGame *glGame, const Vector3 &position, const Vector3 &direction)
        :HasPosition(glGame, position)
        ,direction(direction)
      {
      }
      virtual ~Character(){}

      Vector3 getDirection() const { return direction; }
      void setDirection(const Vector3 &direction) { this->direction = direction; }
    };
  }
}

#endif
