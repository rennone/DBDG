#include <GL/util/glDBDGUtil.h>
#include "PlayScene.h"
#include "Assets.h"
//#include "CameraManager.h"

using DBDG::Util::Actor;
using DBDG::Util::HasPosition;

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

class Player : public  DBDG::Util::Movable
{
  const DBDG::Vector2 initDirection;
public:
  Player(DBDG::GLGame *glGame, const DBDG::Vector3 &position)
    :DBDG::Util::Movable(glGame, position, DBDG::Vector3(0,0,0))
    ,initDirection(0,-1)
  {
    direction.set(initDirection.x, 0, initDirection.y);
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
    float rad = -initDirection.angleTo(DBDG::Vector2(direction.x, direction.z));
    glPushMatrix();
    glTranslated(position.x, position.y, position.z);
    glRotated(rad*DBDG::Vector2::TO_DEGREE, 0, 1, 0);
//    glScaled(100, 100, 100);
    Assets::gargoyle->renderWithColor3(DBDG::Color3(1,0,0));
    glPopMatrix();
  }
};

class PlayerManager : public DBDG::Util::Actor
{
  std::shared_ptr<Player> player;
  std::shared_ptr<DBDG::Util::CameraManager> cameraMgr;  
public:
  PlayerManager(DBDG::GLGame *glGame)
    :DBDG::Util::Actor(glGame)
  {
    player = std::make_shared<Player>(glGame, DBDG::Vector3(0,0,0));
    auto camera     = new DBDG::Util::QuarterViewCamera(glGame->getWindow());
    cameraMgr = std::make_shared<DBDG::Util::CameraManager>(glGame, camera);
    cameraMgr->setZoomSpeed(1000);
    cameraMgr->changeTarget(player);
    addChild(player);
    addChild(cameraMgr);
  }

  void update(const float &delta_time_sec)
  {  
    auto input = glGame->getInput();
    const float speed = 500*delta_time_sec;

    auto direction = DBDG::Vector3(0,0,0);

    auto dirZ = cameraMgr->getCamera()->getLook() - cameraMgr->getCamera()->getPosition();
    dirZ.y = 0;

    auto dirX = dirZ.cross(cameraMgr->getCamera()->getUp());
    bool isMoved = false;
    if(input->getKeyState(GLFW_KEY_W) != GLFW_RELEASE)
    {
      direction += dirZ;
      isMoved = true;
    }
    if(input->getKeyState(GLFW_KEY_S) != GLFW_RELEASE)
    {
      direction -= dirZ;
      isMoved = true;
    }
    if(input->getKeyState(GLFW_KEY_D) != GLFW_RELEASE)
    {
      direction += dirX;
      isMoved = true;
    }
    if(input->getKeyState(GLFW_KEY_A) != GLFW_RELEASE)
    {
      direction -= dirX;
      isMoved = true;
    }

    if(isMoved)
      player->move(direction, speed);
    
    Actor::update(delta_time_sec);
  }

  DBDG::Camera3D* getCamera() const
  {
    return cameraMgr->getCamera();
  }
};
  
PlayScene::PlayScene(DBDG::GLGame *glGame)
  :DBDG::GLScene(glGame)
  ,elapsedTime_sec(0)
{

  playerMgr = new PlayerManager(glGame);
  
  root = new Actor(glGame);
  root->addChild(std::shared_ptr<PlayerManager>(playerMgr));
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
  glPushMatrix();
  playerMgr->getCamera()->setViewportAndMatrices();
  glEnable(GL_DEPTH_TEST);
  DBDG::dbdgDrawGrid(100, 80, 80);
  DBDG::dbdgDrawAxis(1000);

  root->render(delta_time_sec);

  static DBDG::SpriteBatcher3D batcher(30);
  static float elapsed_time_sec = 0;
  elapsed_time_sec += delta_time_sec;

  batcher.clearSprites();
  auto region = Assets::animation->getFrameSprite(elapsed_time_sec);
  batcher.pushSprite(DBDG::Vector3(0,0,0), DBDG::Vector3(0,1,0), DBDG::Vector2(500, 500), region);
  batcher.drawAllSprites(region->texture);
  
  glPopMatrix();
}
