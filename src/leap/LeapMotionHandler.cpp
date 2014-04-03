#include <leap/LeapMotionHandler.h>
#include <leap/leap/Leap.h>

#include <iostream>
using namespace std;

namespace DBDG
{
  class LeapMotionHandler::LeapListener : public Leap::Listener
  {
  public:
    void onConnect(const Leap::Controller &controller);
    void onFrame(const Leap::Controller &controller);
  };

  void LeapMotionHandler::LeapListener::onConnect(const Leap::Controller &controller)
  {
    cout << "LeapMotionListener has Connected " << endl;
  }

  void LeapMotionHandler::LeapListener::onFrame(const Leap::Controller &controller)
  {
    
  }

  LeapMotionHandler::LeapMotionHandler()
  {
    listener = new LeapMotionHandler::LeapListener();
    getController().addListener( *listener );
  }
  
  Leap::Controller& LeapMotionHandler::getController() const
  {
    static Leap::Controller controller;
    return controller;
  }

  const Leap::Frame LeapMotionHandler::getFrame() const
  {
    return getController().frame();
  }
}
