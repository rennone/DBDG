#include <GL/glDBDG.h>
#include <GL/ScrollHandler.h>
#include <Input.h>

namespace DBDG
{
  ScrollHandler::ScrollHandler()
  {
    scrollEvent = new ScrollEvent();
    scrollEventBuffer = new ScrollEvent();
  }

  ScrollHandler::~ScrollHandler()
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    
    //todo use smart pointer
    delete scrollEvent;
    delete scrollEventBuffer;  
  }
  
  ScrollEvent* const ScrollHandler::getScrollEvent() const
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    
    return scrollEvent;
  }

  void ScrollHandler::onEvent(const double &offsetX, const double &offsetY)
  {
    std::lock_guard<std::mutex> lock(mtx_lock);

    scrollEventBuffer->offsetX = offsetX;
    scrollEventBuffer->offsetY = offsetY;
  }

  void ScrollHandler::update()
  {
    std::lock_guard<std::mutex> lock(mtx_lock);
    
    scrollEvent->offsetX = scrollEventBuffer->offsetX;
    scrollEvent->offsetY = scrollEventBuffer->offsetY;
  
    scrollEventBuffer->offsetX = scrollEventBuffer->offsetY = 0;
  }
}
