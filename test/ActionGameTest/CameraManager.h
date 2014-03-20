#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include <GL/Util/Actor.h>

namespace DBDG{
  namespace Util{
    class QuarterViewCamera;
    class Movable;
  }
}


class CameraManager : public DBDG::Util::Actor
{
  DBDG::Util::QuarterViewCamera *camera;
  DBDG::Util::Movable *target; //todo we must use smart pointer
  int upKey, downKey, rightKey, leftKey;
  int yawSpeed_per_sec, pitchSpeed_per_sec;
  int moveToTargetKey, switchTargetModeKey;
  bool doTraceTarget;
  float mouseTranslateSensitivity, mouseRotateSensitivity;
public:
  CameraManager(DBDG::GLGame *glGame, DBDG::Util::QuarterViewCamera *camera);  
  void update(const float &delta_time_sec);
  void changeTarget(DBDG::Util::Movable *target);
  DBDG::Util::QuarterViewCamera* getCamera() {  return camera;  }

private:
  void checkMouse(const float &delta_time_sec);
  void checkKeyboard(const float &delta_time_sec);
  void rotateCamera(const int &delta_yaw, const int &delta_pitch);
  void translateCamera(const int &delta_x, const int &delta_y);
};
#endif
