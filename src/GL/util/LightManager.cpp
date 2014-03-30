#include <GL/glDBDG.h>
#include <GL/LightManager.h>
/*
namespace DBDG
{
  LightManager::LightManager()
    :lightId(
      { GL_LIGHT0, GL_LIGHT1,
        GL_LIGHT2, GL_LIGHT3,
        GL_LIGHT4, GL_LIGHT5,
        GL_LIGHT6, GL_LIGHT7,
          }),
     lightState({false})
  {
  }

  bool setColor(const unsigned int &id, COLOR kind, const Color4 &color)
  {
    if( !within(id) )
      return false;

    
  }
  
  bool LightManager::setLight(const unsigned int &id, const Vector3 &position, const Vector3 &direction)
  {
    if( !within(id) )
      return false;

    glEnagle(lightId[id]);
    glLightfv( lightId[id], GL_POSITION, static_cast<float*>(position) );
    glLightfv( lightId[id], GL_SPOT_DIRECTION, static_cast<float*>(direction) );
    return true;
  }
  
  bool LightManager::killLight(const unsigned int &id) const
  {
    if( !within(id) )
      return false;

    glDisable(lights[id]);
    return true;
  }
  
  int LightManager::getFreeLight() const
  {
    for(int i=0; i<MAX_LIGHT_NUM; i++)
    {
      if( !lightState[i] )
        return i;
    }
    return -1;
  }
}
*/
