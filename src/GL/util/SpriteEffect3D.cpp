#include <GL/util/glDBDGUtil.h>
#include <GL/util/SpriteEffect3D.h>

namespace DBDG
{
  namespace Util
  {
    SpriteEffect3D::SpriteEffect3D(GLGame *_glGame, SpriteAnimation* _effect,const float &_effect_time )
      :Movable(_glGame)     
      ,effectAnimation(_effect)
      ,effectTime(_effect_time)
      ,elapsedTime(0)
      {
        Actor::setStatus(ActorStatus::NoUse);
      }
    
    void SpriteEffect3D::update(const float &delta_time_sec)
    {
      elapsedTime += delta_time_sec;
      if(elapsedTime > effectTime)
        Actor::setStatus(ActorStatus::NoUse);
    }

    void SpriteEffect3D::start(const Vector3 &_position, const Vector3 &_normal, const Vector2 &_size)
    {
      Movable::setPosition(_position);
      Movable::setDirection(_normal);
      size = _size;
      Actor::setStatus(ActorStatus::Action);
      elapsedTime = 0;
    }
  }
}
