#ifndef DBDG_CAMERA_3D_H
#define DBDG_CAMERA_3D_H

#include "../math/Vector3.hpp"
#include "../math/Vector2.hpp"

struct GLFWwindow;
namespace DBDG
{
  class Camera3D
  {
    GLFWwindow *window; //glfwの関数に渡す為constにできない
    //画面上での位置, サイズ
    int viewportX;
    int viewportY;
    int viewportWidth;  //横幅
    int viewportHeight; //縦幅

    //ワールド座標におけるカメラの位置と視野幅,高さ
    Vector3 position;
    Vector3 look;
    Vector3 up; //カメラの上の方向 (基本は(0,1,0))
    float frustumNear, frustumFar;
    float frustumFOVY;  //視野
  public:
    Camera3D(GLFWwindow *window, const float &frustumNear, const float &frustumFar, const float &frustumFOVY);  
    Camera3D(GLFWwindow *window, const Vector3 &position, const Vector3 &look, const float &frustumNear, const float &frustumFar, const float &frustumFOVY);
    ~Camera3D() {  }  

    void setViewportAndMatrices() const;    
    Vector3 screenToWorld(const Vector2 &touch) const;
    Vector2 worldToScreen(const Vector3 &point) const;

    //ゲーム空間上のパラメータ
    Vector3 getPosition() const{  return position; }
    Vector3 getLook() const    {  return look; }    
    Vector3 getUp() const      {  return up; }
    float getFOV() const       {  return frustumFOVY; }
    float getNear() const      {  return frustumNear; }
    float getFar() const       {  return frustumFar; }
    void setPosition(const Vector3 &_position) {  position = _position;  }
    void setLook(const Vector3 &_look)         { look = _look;  }
    void setUp(const Vector3 &_up)             { up = _up; }
    void setFOV(const float &fov)              { frustumFOVY = fov; }
    void setNear(const float &near)            { frustumNear = near; }
    void setFar(const float &far)              { frustumFar = far; }
    
    //スクリーン上の画面のサイズ
    int getViewportWidth() const  { return viewportWidth;  }
    int getViewportHeight() const { return viewportHeight; }
    Vector2 getViewportSize() const {return Vector2(viewportWidth, viewportHeight);}
    void setViewportWidth(const int &width) {  viewportWidth = width;  }  
    void setViewportHeight(const int &height){ viewportHeight = height; }
    void setViewportSize(const int &width, const int &height) { viewportWidth = width; viewportHeight = height;}

    //スクリーン上の画面の位置
    int getViewportX() const { return viewportX; }
    int getViewportY() const { return viewportY; }
    Vector2 getViewportPosition() const { return Vector2(viewportX, viewportY);  } 
    void setViewportX(const int &x) { viewportX = x; }
    void setViewportY(const int &y) { viewportY = y; }
    void setViewportPosition(const int &x, const int &y) { viewportX = x; viewportY = y;  }

    //void perspective() const;  
    //void lookAt() const;
  };
}
#endif
