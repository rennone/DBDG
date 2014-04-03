/*
#include <GLFW/glfw3.h>
#include <GL/GLInput.h>
#include <GL/MouseHandler.h>
#include <GL/KeyboardHandler.h>
#include <GL/ScrollHandler.h>
*/
#include <GL/glDBDG.h>
#include <GL/GLInput.h>

//シングルトン用のマクロ
#define g_KeyboardHandler KeyboardHandler::getInstance()
#define g_MouseHandler MouseHandler::getInstance()

namespace DBDG
{
  GLInput::GLInput()
  {

  }
  
  GLInput::~GLInput()
  {
  }

  void GLInput::update()
  {
    g_KeyboardHandler->update();
    g_MouseHandler->update();
//    scrollHandler->update();
  }

  bool GLInput::isAnyKeyPressed() const
  {
    return g_KeyboardHandler->isAnyKeyPressed();
  }

  bool GLInput::isKeyPressed(const int &key_code) const
  {
    return g_KeyboardHandler->isKeyPressed(key_code);
  }

  int GLInput::getKeyState(const int &key_code) const
  {
    return g_KeyboardHandler->getKeyState(key_code);
  }

  const std::vector<KeyEvent*>& GLInput::getKeyEvents() const
  {
    return g_KeyboardHandler->getKeyEvents();
  }

  const MouseEvent* const GLInput::getMouseEvent() const
  {
    return g_MouseHandler->getMouseEvent();
  }

  //TODO
  const ScrollEvent* const GLInput::getScrollEvent() const
  {
    return nullptr;//g_ScrollHandler->getScrollEvent();
  }

  Vector2 GLInput::getCursorPos() const
  {
    const auto mouse_event = g_MouseHandler->getMouseEvent();
    
    return Vector2((float)mouse_event->x, (float)mouse_event->y);
  }

  void GLInput::onMouseButtonCallback(const int &button, const int &action, const int &mods)
  {
    g_MouseHandler->onButtonEvent(button, action, mods);
  }

  void GLInput::onMouseCursorCallback(const double &_x, const double &_y)
  {
    g_MouseHandler->onCursorEvent(_x, _y);
  }

  void GLInput::onScrollCallback(const double &offsetX,const double &offsetY)
  {
    g_MouseHandler->onScrollEvent(offsetX, offsetY);
  }
  
  void GLInput::onKeyCallback(const int &keyCode, const int &action, const int &mods)
  {
    g_KeyboardHandler->onEvent(keyCode, action, mods);
  }
  
}

