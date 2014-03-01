#include <GL/ScrollHandler.h>
#include <Input.h>
#include <Lock.h>

namespace DBDG
{
  ScrollHandler::ScrollHandler()
  {
    pthread_mutex_init(&lock, NULL);
    scrollEvent = new ScrollEvent();
    scrollEventBuffer = new ScrollEvent();
  }

  ScrollHandler::~ScrollHandler()
  {
    Lock lck(&lock);
    
    //todo use smart pointer
    delete scrollEvent;
    delete scrollEventBuffer;  
  }
  
  ScrollEvent* const ScrollHandler::getScrollEvent() const
  {
    Lock lck(&lock);    
    return scrollEvent;
  }

  void ScrollHandler::onEvent(const double &offsetX, const double &offsetY)
  {
    Lock lck(&lock);
    scrollEventBuffer->offsetX = offsetX;
    scrollEventBuffer->offsetY = offsetY;
  }

  void ScrollHandler::update()
  {
    Lock lck(&lock);
    scrollEvent->offsetX = scrollEventBuffer->offsetX;
    scrollEvent->offsetY = scrollEventBuffer->offsetY;
  
    scrollEventBuffer->offsetX = scrollEventBuffer->offsetY = 0;
  }
}
