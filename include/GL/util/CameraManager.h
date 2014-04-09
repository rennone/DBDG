#ifndef DBDG_UTIL_CAMERA_MANAGER_H
#define DBDG_UTIL_CAMERA_MANAGER_H

#include "Actor.h"
#include "ThirdPersonCamera.h"
#include <memory>

namespace DBDG
{
  namespace Util
  {
    class CameraManager : public Actor
    {
      QuarterViewCamera *camera;
      std::shared_ptr<HasPosition> target;
      unsigned int upKey, downKey, rightKey, leftKey;      
      unsigned int moveToTargetKey, switchTargetModeKey;
      unsigned int zoomInKey, zoomOutKey;

      int yawSpeed_per_sec, pitchSpeed_per_sec;
      int zoomSpeed_per_sec;
      bool doTraceTarget; 
      bool canMouseControl;
      float zoomSensitivity; //
      float mouseTranslateSensitivity, mouseRotateSensitivity;
    public :
      CameraManager(GLGame *glGame, QuarterViewCamera *camera);
      ~CameraManager(){}
      void update(const float &delta_time_sec);
      void changeTarget(std::shared_ptr<HasPosition> target);
      
      void changeControlKey(const unsigned int &yawRightRollKey
                            ,const unsigned int &yawLeftRollKey
                            ,const unsigned int &pitchUprollKey
                            ,const unsigned int &pitchDownrollKey
                            ,const unsigned int &zoomInKey
                            ,const unsigned int &zoomOutKey);
      void setZoomSpeed(const float &zoomSensitivity);
      void setRotateSpeed(const int &yaw_speed_sec, const int &pitch_speed_sec);
      QuarterViewCamera* const getCamera() const { return camera; }

    private:
      void checkMouse(const float &delta_time_sec);
      void checkKeyboard(const float &delta_time_sec);
      void rotateCamera(const int &delta_yaw, const int &delta_pitch);
      void translateCamera(const int &delta_x, const int &delta_y);

      void zoomCamera(const float &delta_radius);
    };
  }
}

#endif
