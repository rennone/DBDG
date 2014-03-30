#ifndef DBDG_GL_UTIL_SPRITE_EFFECT_H
#define DBDG_GL_UTIL_SPRITE_EFFECT_H

#include "Movable.h"
#include "../../SpriteAnimation.h"

namespace DBDG
{
  namespace Util
  {
    class SpriteEffect3D : public Movable
    {
      SpriteAnimation* effectAnimation;
      float effectTime; //エフェクトの終了時間
      float elapsedTime;
      Vector2 size;
    public:
      SpriteEffect3D(GLGame *glGame,
             SpriteAnimation* effect,
             const float &effect_time);
      virtual ~SpriteEffect3D(){}
      virtual void update(const float &delta_time_sec);
      void initialize(SpriteAnimation* effectAnimation, const float &effectTime);
      void start(const Vector3 &_position, const Vector3 &_normal, const Vector2 &_size);
    };
  }
}

#endif
