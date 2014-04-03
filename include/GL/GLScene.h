#ifndef DBDG_GL_SCENE_H
#define DBDG_GL_SCENE_H

#include "../Scene.h"
#include "GLGame.h"

namespace DBDG
{
  class GLGame;
  
  class GLScene:public Scene
  {
  protected:
    GLGame *glGame;
  public:
  GLScene(GLGame *game)
    :Scene(game),glGame(game)
    {
    }  
    virtual void update(const float &deltaTime) = 0;
    virtual void render(const float &deltaTime) = 0;
    virtual void reshape(int width, int height) = 0;
    virtual void dispose() = 0;  
  };
}
#endif
