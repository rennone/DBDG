#ifndef DBDG_LEAP_MOTION_HANDLER_H
#define DBDG_LEAP_MOTION_HANDLER_H

namespace Leap
{
  class Frame;
  class Controller;
  class Listener;
}

namespace DBDG
{
  class LeapMotionHandler
  {
    class LeapListener;
    
    LeapListener *listener;
  public:
    LeapMotionHandler();

    Leap::Controller& getController() const;

    const Leap::Frame getFrame() const;
  };
}

#endif
