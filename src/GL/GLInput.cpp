
#include <GLFW/glfw3.h>
#include <GL/GLInput.h>
#include <GL/MouseHandler.h>
#include <GL/KeyboardHandler.h>
#include <GL/ScrollHandler.h>

namespace DBDG
{
  GLInput::GLInput(GLFWwindow* window)
    :window(window)
  {
    mouseHandler    = std::unique_ptr<MouseHandler>(new MouseHandler(window));
keyboardHandler = std::unique_ptr<KeyboardHandler>(new KeyboardHandler());
scrollHandler   = std::unique_ptr<ScrollHandler>(new ScrollHandler());
  }
  
  GLInput::~GLInput()
  {
  }

  void GLInput::update()
  {
    keyboardHandler->update();
    mouseHandler->update();
    scrollHandler->update();
  }

  bool GLInput::isAnyKeyPressed() const
  {
    return keyboardHandler->isAnyKeyPressed();
  }

  bool GLInput::isKeyPressed(const int &key_code) const
  {
    return keyboardHandler->isKeyPressed(key_code);
  }

  int GLInput::getKeyState(const int &key_code) const
  {
    return keyboardHandler->getKeyState(key_code);
  }

const std::vector<KeyEvent*>& GLInput::getKeyEvents() const
  {
    return keyboardHandler->getKeyEvents();
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
    keyboardHandler->onEvent(keyCode, action, mods);
  }

  void GLInput::onScrollCallback(const double &offsetX,const double &offsetY)
  {
    scrollHandler->onEvent(offsetX, offsetY);
  }
}

