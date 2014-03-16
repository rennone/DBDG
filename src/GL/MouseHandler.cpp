#include <Input.h>
#include <GL/glDBDG.h>
#include <GL/MouseHandler.h>

namespace DBDG
{
  MouseHandler::MouseHandler(GLFWwindow *_window)
    :window(_window)
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    
    mouseEvent = new MouseEvent();
    mouseEventBuffer = new MouseEvent();
  }

  MouseHandler::~MouseHandler()
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    
    delete mouseEvent;
    delete mouseEventBuffer;  
  }
  
  const MouseEvent* const MouseHandler::getMouseEvent() const
  {
    std::lock_guard<std::mutex> lock(mtx_lock);    
    
    return mouseEvent;
  }

  void MouseHandler::onEvent(int button, int action, int mods)
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    
    mouseEventBuffer->button = button;
    mouseEventBuffer->action = action;
    mouseEventBuffer->modifier = mods; 
  }

  void MouseHandler::update()
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
  
    mouseEvent->button   = mouseEventBuffer->button;  //中身をコピー
    mouseEvent->action   = mouseEventBuffer->action;  //中身をコピー
    mouseEvent->modifier = mouseEventBuffer->modifier;
    glfwGetCursorPos(window, &mouseEvent->x, &mouseEvent->y);
  
    if(mouseEventBuffer->action == GLFW_PRESS)
      mouseEventBuffer->action = GLFW_REPEAT;  
  }
}
