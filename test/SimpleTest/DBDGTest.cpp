#include <GL/glDBDG.h>
#include <GL/GLDirector.h>
#include <GL/Tools/SimpleGLFunction.h>
#include <math/Vector3.hpp>
#include <math/Vector2.hpp>

#include <iostream>
#include <cmath>
using namespace std;

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

class CameraManager
{
  DBDG::Camera3D *camera;
  DBDG::GLGame *game;
public:
  CameraManager(DBDG::Camera3D *camera, DBDG::GLGame *game)
    :camera(camera)
    ,game(game)
  {
    
  }

  void update(const float &deltaTime)
  {
    auto events = game->getInput()->getKeyEvents();

    const float speed = 500.0f*deltaTime;
    int dx=0, dy=0, dz=0;
    for( auto it=events.begin(); it!=events.end(); it++)
    {
      if( (*it)->action == GLFW_RELEASE)
        continue;

      if( (*it)->keyCode == GLFW_KEY_UP )
      {
        dy += 10;
      }

      if( (*it)->keyCode == GLFW_KEY_DOWN )
      {
        dy -= 10;
      }

      if( (*it)->keyCode == GLFW_KEY_LEFT )
      {
        dx -= 10;
      }

      if( (*it)->keyCode == GLFW_KEY_RIGHT )
      {
        dx += 10;
      }

      if( (*it)->keyCode == GLFW_KEY_W )
      {
        dz -= 10;
      }

      if( (*it)->keyCode == GLFW_KEY_S )
      {
        dz += 10;
      }
      
    }

    if( dx|dy|dz )
      translate(dx*speed, dy*speed, dz*speed);
  }

  void translate(const float &dx, const float &dy, const float &dz)
  {
    auto axisZ = camera->getLook() - camera->getPosition();
    axisZ.normalize();
    auto axisX = axisZ.cross(camera->getUp());
    axisX.normalize();
    auto axisY = axisX.cross(axisZ);

    auto move = dx*axisX + dy*axisY + dz*axisZ;

    camera->setLook(camera->getLook()+move);
    camera->setPosition(camera->getPosition()+move);
  }
};
  
class TestScene : public DBDG::GLScene
{
  DBDG::Camera2D *camera;
  DBDG::Camera3D *camera3D;
  CameraManager *cameraMgr;
  DBDG::SpriteBatcher *batcher;
  DBDG::SpriteBatcher3D *batcher3D;  
  DBDG::GLTexture *texture;
  DBDG::TextureRegion *region;
  DBDG::XfileModel *model;
  DBDG::GLFont *font;
  float elapsedTime;
public:
  TestScene(DBDG::GLGame *game)
    :DBDG::GLScene(game)
    ,elapsedTime(0)
  {
    camera  = new DBDG::Camera2D(game->getWindow(), 640, 320);
    camera3D= new DBDG::Camera3D(game->getWindow(),DBDG::Vector3(500,500,500), DBDG::Vector3(0,0,0), 1, 3000, 90);
    batcher = new DBDG::SpriteBatcher(50);
    batcher3D = new DBDG::SpriteBatcher3D(50);
    texture = new DBDG::GLTexture("resource/fieldAtlas.png");
    region  = new DBDG::TextureRegion(texture, 0, 0, 128, 128);
    model   = new DBDG::XfileModel("resource/gargoyle/gargoyle.x", 3);

    auto bitmap = new DBDG::GLTexture("resource/bitmapFont.png");
    font = new DBDG::GLFont(bitmap, batcher, batcher3D, /*left = */0, /*top = */0, /* glyphPerRow*/10, 51.2, 51.2);

    cameraMgr = new CameraManager(camera3D, game);
    LightSetting();
  }
  
  void update(const float &deltaTime)
  {
    elapsedTime += deltaTime;
    cameraMgr->update(deltaTime);
  }

  void render(const float &deltaTime)
  {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    camera3D->setViewportAndMatrices();
    DBDG::dbdgDrawGrid(100, 20, 20);
    DBDG::dbdgDrawAxis(1000);
    model->renderWithColor4(DBDG::Color4(1,0,0,1));

    auto dir = camera3D->getPosition() - camera3D->getLook();
    dir.z = 0;
    font->drawString3D("Hello", DBDG::Vector3(0,0,0), dir , 500, 170, DBDG::Color4(1,0,1,1), DBDG::Font::ALIGNMENT_CENTER);
    glPopMatrix();
  }

  void reshape(int width, int height){ }

  void dispose(){ }  
};

class TestGame : public DBDG::GLGame
{
public :
  TestGame(int argc, char **argv, const std::string title, const int window_widht, const int window_height)
    :GLGame(argc, argv, title, window_widht, window_height, false)
  {
  }
  
  DBDG::Scene* getStartScene()
  {
    return new TestScene(this);
  }
};

int main(int argc, char** argv)
{
  TestGame *game = new TestGame(argc, argv, "test", 640, 480);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  DBDG::GLDirector::startGame(game);
  return 0;
}
