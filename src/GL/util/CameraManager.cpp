#include <GL/util/glDBDGUtil.h>
#include <GL/util/CameraManager.h>

namespace DBDG
{
  namespace Util
  {
    CameraManager::CameraManager(GLGame *glGame, QuarterViewCamera *camera)
      :Actor(glGame)
      ,camera(camera)
      ,target(nullptr)
      ,canMouseControl(true)
    {
      setStatus(Actor::ActorStatus::UpdateOnly);
      
      /* default　setting */
      yawSpeed_per_sec   = 240;
      pitchSpeed_per_sec = 240;
      zoomSensitivity  = 100;
      upKey      = GLFW_KEY_UP;
      downKey    = GLFW_KEY_DOWN;
      rightKey   = GLFW_KEY_RIGHT;
      leftKey    = GLFW_KEY_LEFT;
      zoomInKey  = GLFW_KEY_Q;
      zoomOutKey = GLFW_KEY_E;
      switchTargetModeKey = GLFW_KEY_SPACE;
      moveToTargetKey = GLFW_KEY_Z;
      mouseTranslateSensitivity = 10.0f;
      mouseRotateSensitivity = 2.0f;
    }
    
    void CameraManager::changeTarget( std::shared_ptr<Movable> target)
    {
      this->target = target;
    }    

    void CameraManager::update(const float &delta_time_sec)
    {
      checkMouse(delta_time_sec);
      checkKeyboard(delta_time_sec);
  
      if(doTraceTarget && target != NULL)
        camera->setLook(target->getPosition());

      camera->calcPosition();
    }

    void CameraManager::changeControlKey
    (const unsigned int &upKey      , const unsigned int &downKey
     ,const unsigned int &rightKey  , const unsigned int &leftKey
     ,const unsigned int &zoomInKey , const unsigned int &zoomOutKey)
    {
      this->upKey   = upKey;
      this->downKey = downKey;      
      this->rightKey = rightKey;
      this->zoomInKey = zoomInKey;
      this->zoomOutKey = zoomOutKey;
    }

    void CameraManager::setZoomSpeed(const float &zoomSensitivity)
    {
      if( zoomSensitivity < 0 )
        return;
      this->zoomSensitivity = zoomSensitivity;
    }

    void CameraManager::setRotateSpeed(const int &yaw_speed, const int &pitch_speed)
    {
      if(yaw_speed < 0)
        this->yawSpeed_per_sec = yaw_speed;

      if(pitch_speed < 0)
        this->pitchSpeed_per_sec = pitch_speed;      
    }
    
    void CameraManager::checkMouse(const float &delta_time_sec)
    {
      const Input &input = glGame->getInput();
      auto mouseEvent = input.getMouseEvent();
      static Vector2 prevTouchPoint(mouseEvent->x, mouseEvent->y);
      
      if(mouseEvent->action == GLFW_RELEASE)
      {
        prevTouchPoint.set(mouseEvent->x, mouseEvent->y);
        return;
      }

      auto delta_move = Vector2(mouseEvent->x - prevTouchPoint.x,
                                mouseEvent->y - prevTouchPoint.y);

      //ターゲットモードかによって,平行移動か回転かを切り替える
      if( doTraceTarget) {
        delta_move.mul(mouseRotateSensitivity);
        rotateCamera(-delta_move.x, delta_move.y);
      }
      else {
        delta_move.mul(mouseTranslateSensitivity);
        translateCamera(-delta_move.x, delta_move.y);    
      }
  
      prevTouchPoint.set(mouseEvent->x, mouseEvent->y);
    }

    void CameraManager::checkKeyboard(const float &delta_time_sec)
    {  
      const int yaw_move   = ceil(yawSpeed_per_sec*delta_time_sec);
      const int pitch_move = ceil(pitchSpeed_per_sec*delta_time_sec);
      const int radius_move=  ceil(zoomSensitivity*delta_time_sec);
      auto &input = glGame->getInput();
      auto keyEvents = input.getKeyEvents();
      int delta_yaw = 0, delta_pitch = 0, delta_radius = 0;
      for(auto &event : keyEvents)
      {
        if(event->action == GLFW_RELEASE){
          continue;
        }
        else if(event->action == GLFW_PRESS) {
          if(event->keyCode == switchTargetModeKey) {
            doTraceTarget = !doTraceTarget;
            return;
          } else if(event->keyCode == moveToTargetKey && target != NULL) {
            camera->setLook(target->getPosition());
          }
        }
        else {
          if(event->keyCode == upKey)     { delta_pitch += pitch_move;  }
          if(event->keyCode == downKey)   { delta_pitch -= pitch_move;  }
          if(event->keyCode == rightKey)  { delta_yaw += yaw_move;      }
          if(event->keyCode == leftKey)   { delta_yaw -= yaw_move;      }
          if(event->keyCode == zoomInKey) { delta_radius -= radius_move;}
          if(event->keyCode == zoomOutKey){ delta_radius += radius_move;}          
        }
      }

      rotateCamera(delta_yaw, delta_pitch);
      zoomCamera(delta_radius);
    }

//回転可能かのチェックを行う為に, ラップ関数として用意している
    void CameraManager::rotateCamera(const int &delta_yaw, const int &delta_pitch)
    {
      if(!doTraceTarget || target ==NULL)
        return;
  
      camera->rotate(delta_yaw, delta_pitch);
    }

//移動可能かのチェックを行う為に, ラップ関数として用意している
    void CameraManager::translateCamera(const int &delta_x, const int &delta_y)
    {
      if(doTraceTarget)
        return;

      camera->translate(delta_x, delta_y);
    }

    void CameraManager::zoomCamera(const float &delta_radius)
    {
      camera->zoom(delta_radius);
    }

  }
}
