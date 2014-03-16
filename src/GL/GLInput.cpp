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

namespace DBDG
{
  GLInput::GLInput(GLFWwindow* window)
    :window(window)
  {
//    g_KeyboardHandler = std::unique_ptr<KeyboardHandler>(new KeyboardHandler());
    mouseHandler    = std::unique_ptr<MouseHandler>(new MouseHandler(window));    
    scrollHandler   = std::unique_ptr<ScrollHandler>(new ScrollHandler());

  }
  
  GLInput::~GLInput()
  {
  }

  void GLInput::update()
  {
    g_KeyboardHandler->update();
    mouseHandler->update();
    scrollHandler->update();
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
    return mouseHandler->getMouseEvent();
  }

  const ScrollEvent* const GLInput::getScrollEvent() const
  {
    return scrollHandler->getScrollEvent();
  }

  Vector2 GLInput::getCursorPos() const
  {
    double x,y;
    glfwGetCursorPos(window, &x, &y);
    
    return Vector2((float)x, (float)y);
  }

  void GLInput::onMouseCallback(const int &button, const int &action, const int &mods)
  {
    mouseHandler->onEvent(button, action, mods);
  }

  void GLInput::onKeyCallback(const int &keyCode, const int &action, const int &mods)
  {
    g_KeyboardHandler->onEvent(keyCode, action, mods);
  }

  void GLInput::onScrollCallback(const double &offsetX,const double &offsetY)
  {
    scrollHandler->onEvent(offsetX, offsetY);
  }
}

