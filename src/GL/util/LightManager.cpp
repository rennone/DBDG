#include <GL/glDBDG.h>
#include <GL/util/LightManager.h>

namespace DBDG
{
  namespace Util
  {
    LightManager::LightManager()
      :
      lightState(0)
    {
      lightId[0] = GL_LIGHT0;
      lightId[1] = GL_LIGHT1;
      lightId[2] = GL_LIGHT2;
      lightId[3] = GL_LIGHT3;
      lightId[4] = GL_LIGHT4;
      lightId[5] = GL_LIGHT5;
      lightId[6] = GL_LIGHT6;
      lightId[7] = GL_LIGHT7;
    }

    LightManager::~LightManager()
    {
    }

    bool LightManager::setLightColor(const int &id, LightColor kind, const Color4 &color)
    {
      if( !within(id) )
        return false;
      switch(kind)
      {
      case LightColor::Diffuse:
        break;
      case LightColor::Ambient:
        break;
      case LightColor::Specular:
        break;
      default:
        break;
      }
      return true;
    }
  
    bool LightManager::setLightPos(const int &id, const Vector3 &position, const Vector3 &direction)
    {
      if( !within(id) )
        return false;
      glEnable(lightId[id]);

      const GLfloat pos[] = {position.x, position.y, position.z, 1};
      const GLfloat dir[] = {direction.x, direction.y, direction.z, 1};
      glLightfv( lightId[id], GL_POSITION      , pos );
      glLightfv( lightId[id], GL_SPOT_DIRECTION, dir );
      lightState |= (1<<id); //ビットをたてる
      return true;
    }
  
    bool LightManager::killLight(const int &id)
    {
      if( !within(id) || (lightState & (1<<id)) )
        return false;

      glDisable(lightId[id]);
      lightState = lightState ^ (1<<id); //ビットをおろす
      return true;
    }
  
    int LightManager::getFreeLight() const
    {
      for(int i=0; i<MAX_LIGHT_NUM; i++)
      {
        if( !(lightState & (1<<i)) )
          return i;
      }
      return -1;
    }

    void LightManager::killAllLight()
    {
      for(int i=0; i<MAX_LIGHT_NUM; i++)
        killLight(i);    
    }
  }
}
