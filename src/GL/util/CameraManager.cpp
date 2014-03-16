#include <GL/util/glDBDGUtil.h>
#include <GL/util/CameraManager.h>

namespace DBDG
{
  namespace Util
  {
    CameraManager::CameraManager(GLGame *glGame, ThirdPersonCamera *camera)
      :Actor(glGame)
      ,camera(camera)
      ,canMouseControl(true)
      ,zoomSpeed(3)
      ,rotateSpeed(1)
    {
      yawRightRollKey  = GLFW_KEY_D;
      yawLeftRollKey   = GLFW_KEY_A;
      pitchUprollKey   = GLFW_KEY_W;
      pitchDownrollKey = GLFW_KEY_S;
      zoomInKey        = GLFW_KEY_Q;
      zoomOutKey       = GLFW_KEY_E;
    }

    void CameraManager::update(const float &delta_time_sec)
    {
      auto input = glGame->getInput();

      int delta_yaw = 0, delta_pitch = 0;
      if(input->getKeyState(yawRightRollKey) != GLFW_RELEASE)
        delta_yaw -= rotateSpeed;
      
      if(input->getKeyState(yawLeftRollKey) != GLFW_RELEASE)
        delta_yaw += rotateSpeed;

      if(input->getKeyState(pitchUprollKey) != GLFW_RELEASE)
        delta_pitch += rotateSpeed;

      if(input->getKeyState(pitchDownrollKey) != GLFW_RELEASE)
        delta_pitch -= rotateSpeed;

      camera->rotate(delta_yaw, delta_pitch);

      
      if(input->getKeyState(zoomInKey) != GLFW_RELEASE)
        camera->zoom(-1*zoomSpeed);
      
      if(input->getKeyState(zoomOutKey) != GLFW_RELEASE)
        camera->zoom(1*zoomSpeed);      
      
      if(canMouseControl)
      {
        const auto mouseEvent = input->getMouseEvent();
        if(mouseEvent->action != GLFW_RELEASE)
        {
          const auto mousePos = Vector2(mouseEvent->x, mouseEvent->y);
          static auto touchPrev = mousePos;        
          auto dir = touchPrev - mousePos;
          camera->rotate(dir.x, dir.y);
          touchPrev = mousePos;
        }
      }
      
      camera->update(delta_time_sec);
    }

    void CameraManager::changeControlKey
    (const unsigned int &yawRightRollKey,const unsigned int &yawLeftRollKey
     ,const unsigned int &pitchUprollKey,const unsigned int &pitchDownrollKey
     ,const unsigned int &zoomInKey     ,const unsigned int &zoomOutKey)
    {
      this->yawRightRollKey   = yawRightRollKey;
      this->yawLeftRollKey = yawLeftRollKey;      
      this->pitchUprollKey = pitchUprollKey;
      this->pitchDownrollKey  = pitchDownrollKey;
      this->zoomInKey = zoomInKey;
      this->zoomOutKey = zoomOutKey;
    }

    void CameraManager::setZoomSpeed(const int &speed)
    {
      if(speed < 0)
        return;
      zoomSpeed = speed;
    }

    void CameraManager::setRotateSpeed(const int &speed)
    {
      if(speed < 0)
        return;
      
      rotateSpeed = speed;
    }
  }
}
