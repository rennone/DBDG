#ifndef DBDG_UTIL_HAS_POSITION_H
#define DBDG_UTIL_HAS_POSITION_H

#include "Actor.h"
#include "../../math/Vector3.hpp"

namespace DBDG
{
  namespace Util
  {
    class HasPosition : public Actor
    {
    protected:
      Vector3 position;
    public:
      HasPosition(DBDG::GLGame *glGame, const Vector3 &position)
        :Actor(glGame) ,position(position)
      {
      }
      virtual ~HasPosition(){}
        
      const Vector3& getPosition() const
      {
        return position;
      }
    
      void setPosition(const Vector3 &position)
      {
        this->position = position;
      }
    };
  }
}

#endif
