#ifndef QUARTER_VIEW_CAMERA_H
#define QUARTER_VIEW_CAMERA_H

#include <GL/Camera3D.h>

namespace DBDG
{
  namespace Util
  {
    class QuarterViewCamera : public DBDG::Camera3D
    {
      /* y軸回転, x軸か移転、距離 */
      int yaw, pitch, radius;
      int maxPitch, minPitch;
      int maxRadius, minRadius;

    public:
      QuarterViewCamera(GLFWwindow *window);
      void calcPosition();
      void translate(const float &delta_x, const float &delta_y);
      void rotate(const int &delta_yaw, const int &delta_pitch);
      void zoom(const int &delta_radius);
    };
  }
}
   

#endif
