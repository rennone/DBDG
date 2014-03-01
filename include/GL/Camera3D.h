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
    Camera3D(GLFWwindow *window, float _frustumNear, float _frustumFar, float _frustumFOVY);  
    Camera3D(GLFWwindow *window, Vector3 _position, Vector3 _look, float _frustumNear, float _frustumFar, float _frustumFOVY);
    ~Camera3D() {  }  
    
    void setViewportAndMatrices() const;  
  
    Vector3 screenToWorld(const Vector2 &touch) const;

    Vector2 worldToScreen(const Vector3 &point) const;

    void perspective() const;
  
    void lookAt() const;

    Vector3 getPosition() const
    {
      return position;
    }

    Vector3 getLook() const
    {
      return look;
    }
  
    void setPosition(const Vector3 &_position)
    {
      position = _position;
    }

    void setLook(const Vector3 &_look)
    {
      look = _look;
    }

    void setUp(const Vector3 &_up)
    {
      up = _up;    
    }

    Vector3 getUp() const
    {
      return up;    
    }   
  
    //:画面の場所, サイズを変える  
    void setViewportWidth(const int &width)
    {
      viewportWidth = width;
    }
  
    void setViewportHeight(const int &height)
    {
      viewportHeight = height;
    }

    int getViewportWidth() const
    {
      return viewportWidth;    
    }

    int getViewportHeight() const
    {
      return viewportHeight;    
    }  
  
    void setViewportPosition(const int &x, const int &y)
    {
      viewportX = x;
      viewportY = y;
    }

    Vector2 getViewportPosition() const
    {
      return Vector2(viewportX, viewportY);    
    } 

  };
}
#endif
