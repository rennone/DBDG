#ifndef DBDG_GL_UTIL_THIRD_PERSON_CAMERA_H
#define DBDG_GL_UTIL_THIRD_PERSON_CAMERA_H

#include "../Camera3D.h"
#include "Movable.h"
namespace DBDG
{
  namespace Util
  {
    class ThirdPersonCamera : public Camera3D
    {
      Movable *person;  
      int yaw, pitch;
      int maxPitch, minPitch;
      int radius;
      int maxRadius, minRadius;
      Vector3 localPosition;
    public:
      ThirdPersonCamera(GLFWwindow *window, const float &frustumNear, const float &frustumFar, const float &frustumFOVY, Movable *person);
      ThirdPersonCamera(GLFWwindow *window, const Vector3 &position, const Vector3 &look,
                        const float &frustumNear, const float &frustumFar, const float &frustumFOVY, Movable *person);
      void setRadius(const int &radius);
      int getRadius() const { return radius; }
      int getYaw() const { return yaw; }
      int getPitch() const { return pitch; }

      void setPitchLimit(const int &minPitch, const int &maxPitch);
      void setRadiusLimit(const int &minRadius, const int &maxRadius);
      void calcLocalPosition();
      void update(const float &delta_time_sec);

      void rotate(const int &delta_yaw, const int &delta_pitch);
      void zoom(const int &deg);
      
      Movable* const getTargetMovable() { return person; }
    };
  }
}

#endif
