#ifndef DBDG_GL_INPUT_H
#define DBDG_GL_INPUT_H

#include "../Input.h"
#include "../math/Vector2.hpp"
#include <memory>

struct GLFWwindow;
namespace DBDG
{
  class GLGame;
  class MouseHandler;
  class KeyboardHandler;
  class ScrollHandler;
  class LeapMotionHandler;  
  
  class GLInput : public Input
  {
    friend class GLGame;  
    GLFWwindow  *window;

    
    std::unique_ptr<MouseHandler>      mouseHandler;
    //std::unique_ptr<KeyboardHandler>   keyboardHandler;
    std::unique_ptr<ScrollHandler>     scrollHandler;
    
//    std::unique_ptr<LeapMotionHandler> leapMotionHandler;

  public:
    GLInput(GLFWwindow *window);  
    ~GLInput();  

    void update();    
    bool isAnyKeyPressed() const;
    bool isKeyPressed(const int &keyCode) const;
    int getKeyState(const int &keyCode) const;
    const std::vector<KeyEvent*>& getKeyEvents() const;  
    const MouseEvent* const getMouseEvent() const;
    const ScrollEvent* const getScrollEvent() const;
    Vector2 getCursorPos() const;

    //イベント発生時にGameクラスから呼ばれる
    void onMouseCallback(const int &button,const int &action,const int &mods);
    void onKeyCallback(const int &keyCode,const int &action,const int &mods);
    void onScrollCallback(const double &offsetX,const double &offsetY);
  };  
}

#endif
