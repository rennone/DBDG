#ifndef DBDG_MOUSE_HANDLER_H
#define DBDG_MOUSE_HANDLER_H

#include <mutex>

namespace DBDG
{
  class MouseEvent;
  class MouseHandler
  {
    MouseEvent *mouseEvent, *mouseEventBuffer;
    mutable std::mutex mtx_lock;
    
    MouseHandler();
    MouseHandler(const MouseHandler &other);
    MouseHandler& operator=(const MouseHandler &other);
    ~MouseHandler();      
  public:    
    static MouseHandler* getInstance()
    {
      static MouseHandler instance;
      return &instance;
    }    
    const MouseEvent* const getMouseEvent() const;
    void onButtonEvent(const int &button, const int &action, const int &mods);
    void onCursorEvent(const double &_x, const double &_y);
    void onScrollEvent(const double &_offset_x, const double &_offset_y);
    void update();
  };  
}

#endif
