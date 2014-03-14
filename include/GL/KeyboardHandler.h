#ifndef DBDG_KEYBOARD_HANDLER_H
#define DBDG_KEYBOARD_HANDLER_H

#include "../Pool.h"
#include "../Input.h"
#include <vector>
#include <pthread.h>

namespace DBDG
{  
  class KeyboardHandler
  {
    class KeyEventFactory:public PoolObjectFactory<KeyEvent>
    {
      KeyEvent* createObject()
      {
        return new KeyEvent();
      }
    };

    static constexpr int keyMapSize = 350; //GLFWのキー定数の最大数
    int pressedKeys[keyMapSize];

    Pool<KeyEvent> *keyEventPool;
    std::vector<KeyEvent*> keyEvents;
    std::vector<KeyEvent*> keyEventBuffer;
    mutable pthread_mutex_t lock;
    KeyboardHandler();
    KeyboardHandler(const KeyboardHandler& other);
    KeyboardHandler& operator=(const KeyboardHandler &other);
  public:
    static KeyboardHandler* getInstance()
    {
      static KeyboardHandler instance;
      return &instance;
    }
    ~KeyboardHandler();
    
    bool isAnyKeyPressed();
    bool isKeyPressed(int keyCode);  
    int getKeyState(int keyCode);
    const std::vector<KeyEvent*>& getKeyEvents();  
    void onEvent(const int &keyCode,const int &action, const int &mods);
    void update();
  };
}
#endif
