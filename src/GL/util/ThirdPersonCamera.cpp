#include <GL/util/glDBDGUtil.h>
#include <GL/util/ThirdPersonCamera.h>
#include <algorithm>
#include <cmath>

namespace DBDG
{
  namespace Util
  {

    ThirdPersonCamera::ThirdPersonCamera(GLFWwindow *window, const float &frustum_near, const float &frustum_far, const float &frustum_FOVY, Movable *person)
      :Camera3D(window, frustum_near, frustum_far, frustum_FOVY)
      ,person(person)
      ,yaw(45)
      ,pitch(0)
      ,maxPitch(89)
      ,minPitch(-89)
      ,radius(1000)
      ,maxRadius(2000)
      ,minRadius(300)
    {
      
      calcLocalPosition();
    }
    
    ThirdPersonCamera::ThirdPersonCamera(GLFWwindow *window, const Vector3 &position, const Vector3 &look,
                        const float &frustum_near, const float &frustum_far, const float &frustum_FOVY, Movable *person)
      :Camera3D(window, position, look, frustum_near, frustum_far, frustum_FOVY)
      ,person(person)
      ,yaw(0)
      ,pitch(45)
      ,maxPitch(89)
      ,minPitch(-89)
      ,radius(1000)
      ,maxRadius(2000)
      ,minRadius(300)
    {
      calcLocalPosition();
    }

    void ThirdPersonCamera::setPitchLimit(const int &minPitch, const int &maxPitch)
    {
      this->minPitch = fmin(89, fmax(-89, minPitch));
      this->maxPitch = fmin(89, fmax(-89, maxPitch));
      if(minPitch > maxPitch)
        std::swap(this->minPitch, this->maxPitch);
    }
    
    void ThirdPersonCamera::setRadius(const int &radius)
    {
      this->radius = radius;
    }
    
    void ThirdPersonCamera::calcLocalPosition()
    {
      const float yaw_rad   = yaw*Vector3::TO_RADIANS;
      const float pitch_rad = pitch*Vector3::TO_RADIANS;
      const float rad_cos_pitch = radius*cos(pitch_rad);
      localPosition.set(rad_cos_pitch*sin(yaw_rad) ,
                        radius*sin(pitch_rad) ,
                        rad_cos_pitch*cos(yaw_rad));
    }
  
    void ThirdPersonCamera::update(const float &delta_time_sec)
    {
      calcLocalPosition();
      setPosition(localPosition + person->getPosition());
      setLook(person->getPosition());
    }

    void ThirdPersonCamera::rotate(const int &delta_yaw, const int &delta_pitch)
    {
      yaw += delta_yaw;
      if(yaw < 0)       yaw+=360;
      else if(yaw>360)  yaw-=360;
      
      pitch += delta_pitch;
      pitch = std::min(maxPitch, std::max(minPitch, pitch));      
    }
    
    void ThirdPersonCamera::zoom(const int &deg)
    {
      radius += deg;
      radius = std::min(maxRadius, std::max(minRadius, radius));
    }
  }
}
