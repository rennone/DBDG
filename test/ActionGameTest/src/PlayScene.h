#ifndef ACTION_TEST_PLAY_SCENE_H
#define ACTION_TEST_PLAY_SCENE_H

#include <GL/glDBDG.h>
#include <GL/util/glDBDGUtil.h>
#include <memory>

class Player;
class PlayerManager;

class PlayScene : public DBDG::GLScene
{
  float elapsedTime_sec;
  std::shared_ptr<PlayerManager> playerMgr;
  std::shared_ptr<DBDG::Util::Actor> root;
public :
  PlayScene(DBDG::GLGame *glGame);
  ~PlayScene();  

  void update(const float &delta_time_sec);
  void render(const float &delta_time_sec);
  void reshape(int width, int height)
  {
  }
  
  void dispose()
  {
  }
};

#endif
