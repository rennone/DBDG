#ifndef DBDG_MOUSE_HANDLER_H
#define DBDG_MOUSE_HANDLER_H

#include <mutex>
struct GLFWwindow;
namespace DBDG
{
  class MouseEvent;
  class MouseHandler
  {
    //TODO use smart pointer
    GLFWwindow *window;    
    MouseEvent *mouseEvent, *mouseEventBuffer;
    mutable std::mutex mtx_lock;
  public:
    MouseHandler(GLFWwindow *window);  
    ~MouseHandler();  
    const MouseEvent* const getMouseEvent() const; 
    void onEvent(int button, int action, int mods);
    void update();  
  };  
}

#endif
