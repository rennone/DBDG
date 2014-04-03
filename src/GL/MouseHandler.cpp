#include <Input.h>
#include <GL/glDBDG.h>
#include <GL/MouseHandler.h>

namespace DBDG
{
  MouseHandler::MouseHandler()   
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    
    mouseEvent       = new MouseEvent();
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

  void MouseHandler::onButtonEvent(const int &button, const int &action, const int &mods)
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    
    mouseEventBuffer->button = button;
    mouseEventBuffer->action = action;
    mouseEventBuffer->modifier = mods; 
  }

  void MouseHandler::onCursorEvent(const double &_x, const double &_y)
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    mouseEventBuffer->x = _x;
    mouseEventBuffer->y = _y;
  }

  void MouseHandler::onScrollEvent(const double &_offset_x, const double &_offset_y)
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    mouseEventBuffer->scrollOffsetX = _offset_x;
    mouseEventBuffer->scrollOffsetY = _offset_y;
  }
  
  void MouseHandler::update()
  {
    std::lock_guard<std::mutex> lock(mtx_lock);

    //カーソルの差分を計算
    mouseEvent->velosityX     = mouseEventBuffer->x - mouseEvent->x;
    mouseEvent->velosityY     = mouseEventBuffer->y - mouseEvent->y;
    //バッファをコピー
    mouseEvent->x             = mouseEventBuffer->x;
    mouseEvent->y             = mouseEventBuffer->y;
    mouseEvent->button        = mouseEventBuffer->button;
    mouseEvent->action        = mouseEventBuffer->action;
    mouseEvent->modifier      = mouseEventBuffer->modifier;
    mouseEvent->scrollOffsetX = mouseEventBuffer->scrollOffsetX;
    mouseEvent->scrollOffsetY = mouseEventBuffer->scrollOffsetY;
  
    if(mouseEventBuffer->action == GLFW_PRESS)
      mouseEventBuffer->action = GLFW_REPEAT;  
  }
}
