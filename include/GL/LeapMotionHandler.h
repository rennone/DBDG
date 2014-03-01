#ifndef DBDG_LEAP_MOTION_HANDLER_H
#define DBDG_LEAP_MOTION_HANDLER_H

//#include "Leap/Leap.h"

using namespace Leap;
/*
class SyukatsuListener:public Listener
{
public:
  virtual void onInit(const Leap::Controller& leap)
  {
    leap.enableGesture( Leap::Gesture::TYPE_SCREEN_TAP );
    leap.enableGesture( Leap::Gesture::TYPE_KEY_TAP );
    leap.enableGesture( Leap::Gesture::TYPE_CIRCLE );
    leap.enableGesture( Leap::Gesture::TYPE_SWIPE );
  }
};
*/

namespace DBDG
{
  class LeapMotionHandler
  {
    Frame lastFrame;
    Controller *controller;
  
  public:
    LeapMotionHandler()
    {
      //controller.addListener( Listener );    
    }

    Controller* getController() const
    {
      return controller;    
    }

    Frame getFrame() const
    {
      return lastFrame;    
    }  
  };
}
#endif
