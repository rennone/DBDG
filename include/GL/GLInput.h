#ifndef DBDG_GL_INPUT_H
#define DBDG_GL_INPUT_H

#include "../Input.h"
#include "../math/Vector2.hpp"
#include <memory>

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
//    std::unique_ptr<LeapMotionHandler> leapMotionHandler;
    
    GLInput(const GLInput &other);
    GLInput& operator=(const GLInput &other);
    ~GLInput();
    //イベント発生時にGameクラスから呼ばれる

  public:
    GLInput();
    bool isAnyKeyPressed() const;
    bool isKeyPressed(const int &keyCode) const;
    int getKeyState(const int &keyCode) const;
    const std::vector<KeyEvent*>& getKeyEvents() const;  
    const MouseEvent* const getMouseEvent() const;
    const ScrollEvent* const getScrollEvent() const;
    Vector2 getCursorPos() const;

    void update();
    void onMouseButtonCallback(const int &button,const int &action,const int &mods);
    void onMouseCursorCallback(const double &_x, const double &_y);
    void onKeyCallback(const int &keyCode,const int &action,const int &mods);
    void onScrollCallback(const double &offsetX,const double &offsetY);    
  };  
}

#endif
