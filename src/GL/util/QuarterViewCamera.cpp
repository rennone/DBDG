#include <GL/util/glDBDGUtil.h>
#include <GL/util/QuarterViewCamera.h>
#include <algorithm>

namespace DBDG
{
  namespace Util
  {
    QuarterViewCamera::QuarterViewCamera(GLFWwindow *window)
      :DBDG::Camera3D( window
		       ,/* position =*/ DBDG::Vector3(0,0,0)
		       , /* look = */ DBDG::Vector3(0,0,1)
		       ,/* near = */ 1
		       ,/* far  = */3000
		       ,/* fovy = */90 )
      ,maxPitch(89),minPitch(0)
      ,maxRadius(3000), minRadius(100)
      ,yaw(0), pitch(45), radius(1000)
    {
  
    }

    void QuarterViewCamera::calcPosition()
    {
      const float rad_yaw   = yaw*DBDG::Vector3::TO_RADIANS;
      const float rad_pitch = pitch*DBDG::Vector3::TO_RADIANS;
      const float r_cos_pitch = radius*cos(rad_pitch);
      const float r_sin_pitch = radius*sin(rad_pitch);
      DBDG::Vector3 localPosition(r_cos_pitch*cos(rad_yaw)
				  ,r_sin_pitch
				  ,r_cos_pitch*sin(rad_yaw));
      setPosition(getLook() + localPosition);
    }

    void QuarterViewCamera::zoom(const int &delta_radius)
    {
      radius = std::min(maxRadius, std::max(minRadius, radius+delta_radius));
    }

    void QuarterViewCamera::translate(const float &delta_x, const float &delta_y)
    {
      auto axis_z = getLook() - getPosition();
      auto axis_x = axis_z.cross(getUp());
      auto axis_y = axis_x.cross(axis_z);
      axis_x.normalize();
      axis_y.normalize();

      setLook(getLook() + delta_x*axis_x + delta_y*axis_y);
    }

    void QuarterViewCamera::rotate(const int &delta_yaw, const int &delta_pitch)
    {
      yaw += delta_yaw;
      if(yaw < 0)         yaw += 360;
      else if(yaw > 360)  yaw -= 360;

      pitch = std::min(maxPitch, std::max(minPitch, pitch+delta_pitch));
    }
  }
}
