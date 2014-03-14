#include "PlayScene.h"
#include "Assets.h"
#include <GL/util/glDBDGUtil.h>
#include <GL/GLFW/glfw3.h>

using DBDG::Util::Actor;
using DBDG::Util::HasPosition;
using DBDG::Util::CameraManager;
using DBDG::Util::ThirdPersonCamera;
static void LightSetting()
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);

  float edge = 800;
  GLfloat lightpos1[] = { 0.0, edge/2, 0.0, 1.0 };
  GLfloat lightdir1[] = { 1.0, -1.0, 1.0, 1.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos1);
  glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lightdir1);
  
  GLfloat lightpos2[] = { edge, edge/2, edge, 1.0 };
  GLfloat lightdir2[] = { -1.0, -1.0, -1.0, 1.0 };
  glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lightdir2);
 
  GLfloat lightpos3[] = { 0.0, edge/2, edge, 1.0 };
  GLfloat lightdir3[] = { 1.0, -1.0, -1.0, 1.0 };
  glLightfv(GL_LIGHT2, GL_POSITION, lightpos3);
  glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lightdir3);
 
  GLfloat lightpos4[] = { edge, edge/2, 0.0, 1.0 };
  GLfloat lightdir4[] = { -1.0, -1.0, 1.0, 1.0 };
  glLightfv(GL_LIGHT4, GL_POSITION, lightpos4);
  glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lightdir4); 
}

class Player : public  DBDG::Util::Character
{
public:
  Player(DBDG::GLGame *glGame, const DBDG::Vector3 &position, const DBDG::Vector3 &direction)
    :DBDG::Util::Character(glGame, position, direction)
  { 
  }
  
  void update(const float &delta_time_sec)
  {
  }

  void move(const DBDG::Vector3 &direction, const float &speed)
  {
    this->direction.set(direction.x, direction.y, direction.z);
    this->direction.normalize();
    this->position += this->direction*speed;
  }
  
  void render(const float &delta_time_sec)
  {
    glPushMatrix();
    glTranslated(position.x, position.y, position.z);
    Assets::gargoyle->render();
    glPopMatrix();
  }
};

class PlayerManager : public DBDG::Util::Actor
{
  Player* const player;
  CameraManager* const cameraMgr;  
public:
  PlayerManager(DBDG::GLGame *glGame, Player* player, CameraManager *cameraMgr)
    :DBDG::Util::Actor(glGame)
    ,player(player)
    ,cameraMgr(cameraMgr)
  {
    addChild(player);
    addChild(cameraMgr);
  }

  void update(const float &delta_time_sec)
  {  
    auto input = glGame->getInput();
    const float speed = 500*delta_time_sec;
    
    if(input->getKeyState(GLFW_KEY_UP) != GLFW_RELEASE)
    {
      auto direction = cameraMgr->getCamera()->getLook() - cameraMgr->getCamera()->getPosition();
      direction.y = 0;
      player->move(direction, speed);
    }

    if(input->getKeyState(GLFW_KEY_DOWN) != GLFW_RELEASE)
    {
      auto direction = -(cameraMgr->getCamera()->getLook() - cameraMgr->getCamera()->getPosition());
      direction.y = 0;
      player->move(direction, speed);
    }
    
    Actor::update(delta_time_sec);
  }

  ThirdPersonCamera* getCamera() const
  {
    return cameraMgr->getCamera();
  }
};
  
PlayScene::PlayScene(DBDG::GLGame *glGame)
  :DBDG::GLScene(glGame)
  ,elapsedTime_sec(0)
{
  auto player = new Player(glGame, DBDG::Vector3(0,0,0), DBDG::Vector3(0,0,1));
  auto camera = new ThirdPersonCamera(glGame->getWindow(),
                                      DBDG::Vector3(500,500,500),
                                      DBDG::Vector3(0,0,0),
                                      1, 3000, 90, player);
  
  auto cameraMgr = new CameraManager(glGame, camera);
  playerMgr = new PlayerManager(glGame, player, cameraMgr);
  
  root = new Actor(glGame);
  root->addChild(playerMgr);
  LightSetting();
}

PlayScene::~PlayScene()
{
  
}

void PlayScene::update(const float &delta_time_sec)
{
  elapsedTime_sec += delta_time_sec;
  
  auto events = glGame->getInput()->getKeyEvents();
  for( auto event : events )
  {
    if(event->action != GLFW_PRESS)
      continue;
//    Assets::akan->play();
  }

  root->update(delta_time_sec);
}

void PlayScene::render(const float &delta_time_sec)
{
//  camera3D->setViewportAndMatrices();
  playerMgr->getCamera()->setViewportAndMatrices();
  DBDG::dbdgDrawGrid(100, 80, 80);
  DBDG::dbdgDrawAxis(1000);
//  Assets::gargoyle->render();
  root->render(delta_time_sec);
}