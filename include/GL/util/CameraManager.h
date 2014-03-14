#ifndef DBDG_UTIL_CAMERA_MANAGER_H
#define DBDG_UTIL_CAMERA_MANAGER_H

#include "Actor.h"
#include "ThirdPersonCamera.h"

namespace DBDG
{
  namespace Util
  {
    class CameraManager : public Actor
    {
      ThirdPersonCamera *camera;
      unsigned int yawRightRollKey, yawLeftRollKey;
      unsigned int pitchUprollKey, pitchDownrollKey;
      unsigned int zoomInKey, zoomOutKey;      
      bool canMouseControl;
      int zoomSpeed;
      int rotateSpeed;
    public :
      CameraManager(GLGame *glGame, ThirdPersonCamera *camera);
      ~CameraManager(){}
      void update(const float &delta_time_sec);
      void changeControlKey(const unsigned int &yawRightRollKey
                            ,const unsigned int &yawLeftRollKey
                            ,const unsigned int &pitchUprollKey
                            ,const unsigned int &pitchDownrollKey
                            ,const unsigned int &zoomInKey
                            ,const unsigned int &zoomOutKey);
      void setZoomSpeed(const int &speed);
      void setRotateSpeed(const int &speed);
      ThirdPersonCamera* const getCamera() const { return camera; }

    private:
      
    };
  }
}

#endif
