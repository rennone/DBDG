#include <GL/glDBDG.h>
#include <math/Vector3.hpp>
#include <math/Vector2.hpp>
#include "PlayScene.h"
#include "Assets.h"
#include <iostream>
#include <cmath>

class ActionGame : public DBDG::GLGame
{
public :
  ActionGame(int argc, char **argv, const std::string title, const int window_widht, const int window_height)
    :GLGame(argc, argv, title, window_widht, window_height, false)
  {
    Assets::loadAssets();    
  }
  
  DBDG::Scene* getStartScene()
  {
    return new PlayScene(this);
  }
};

int main(int argc, char** argv)
{
  ActionGame *game = new ActionGame(argc, argv, "test", 640, 480);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  DBDG::GLDirector::startGame(game);
  return 0;
}
