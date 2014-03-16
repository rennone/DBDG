#include <GL/glDBDG.h>
#include <GL/Util/glDBDGUtil.h>
#include "CameraManager.h"
#include "QuarterViewCamera.h"

CameraManager::CameraManager(DBDG::GLGame *glGame, QuarterViewCamera *camera)
  :Actor(glGame),camera(camera),target(NULL),doTraceTarget(false)
{
  setStatus(DBDG::Util::Actor::UpdateOnly);

  /* todo ユーザ設定から読み込むようにする　*/
  yawSpeed_per_sec   = 240;
  pitchSpeed_per_sec = 240;
  upKey   = GLFW_KEY_W;
  downKey = GLFW_KEY_S;
  rightKey= GLFW_KEY_D;
  leftKey = GLFW_KEY_A;
  switchTargetModeKey = GLFW_KEY_SPACE;
  moveToTargetKey = GLFW_KEY_Z;
  mouseTranslateSensitivity = 10.0f;
  mouseRotateSensitivity = 2.0f;
}

void CameraManager::changeTarget(DBDG::Util::Character *target)
{
  if(target != NULL)
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

void CameraManager::checkMouse(const float &delta_time_sec)
{
  auto input = glGame->getInput();
  auto mouseEvent = input->getMouseEvent();
  static DBDG::Vector2 prevTouchPoint(mouseEvent->x, mouseEvent->y);
  if(mouseEvent->action == GLFW_RELEASE)
  {
    prevTouchPoint.set(mouseEvent->x, mouseEvent->y);
    return ;
  }

  auto delta_move = DBDG::Vector2(mouseEvent->x - prevTouchPoint.x,
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
  
  auto input = glGame->getInput();
  auto keyEvents = input->getKeyEvents();
  int delta_yaw = 0, delta_pitch = 0;
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
      if(event->keyCode == upKey){
        delta_pitch += pitch_move;
      }
      else if(event->keyCode == downKey){
        delta_pitch -= pitch_move;
      }
      else if(event->keyCode == rightKey){
        delta_yaw += yaw_move;
      }
      else if(event->keyCode == leftKey){
        delta_yaw -= yaw_move;
      }
    }
  }

  rotateCamera(delta_yaw, delta_pitch);
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
