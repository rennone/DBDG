#ifndef DBDG_SCROLL_HANDLER_H
#define DBDG_SCROLL_HANDLER_H

#include <pthread.h>

namespace DBDG
{
  class ScrollEvent;
  class ScrollHandler
  {
    ScrollEvent *scrollEvent, *scrollEventBuffer;
    mutable pthread_mutex_t lock;
  public:
    ScrollHandler();
    ~ScrollHandler();  
    ScrollEvent* const getScrollEvent() const;
    void onEvent(const double &offsetX, const double &offsetY);
    void update();
  };
}

#endif
