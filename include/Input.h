#ifndef DBDG_INPUT_H
#define DBDG_INPUT_H

#include <vector>
namespace DBDG
{
  class KeyEvent
  {
  public:
    int action;    //押したか離したか
    int keyCode;   //押したキー
    int modifier;  //Shift, Ctrl, Alt, Superキー用  
  };

  class MouseEvent
  {
  public:    
    int action;   //押した, 離した, ドラッグ
    int button;   //右クリックか左クリックか
    int modifier; //Shift, Ctrl, Alt, Superキー用
    double x, y;
    double velosityX, velosityY;
    double scrollOffsetX, scrollOffsetY;
  };

  class ScrollEvent
  {
  public:
    double offsetX;
    double offsetY;  
  };

  class LeapMotionHandler;

  class Input
  {
    Input(const Input&);
    Input& operator=(const Input&);
  public:
    Input(){}
    virtual ~Input(){}
    
    virtual bool isAnyKeyPressed() const = 0;
    virtual bool isKeyPressed(const int &keyCode) const = 0;
    virtual int getKeyState(const int &keyCode) const = 0;
    
    virtual const MouseEvent*  const getMouseEvent() const = 0;
    virtual const ScrollEvent* const getScrollEvent() const = 0;
    virtual const std::vector<KeyEvent*>& getKeyEvents() const = 0;

    //virtual LeapMotionHandler* getLeapMotionHandler() const = 0;  
  };
}

#endif
