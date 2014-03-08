#include <GL/glDBDG.h>
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

class TestScene : public DBDG::GLScene
{
  DBDG::Camera2D *camera;
  DBDG::Camera3D *camera3D;  
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
    camera3D= new DBDG::Camera3D(game->getWindow(),DBDG::Vector3(500,500,500), DBDG::Vector3(0,0,0), 1, 1000, 120);
    batcher = new DBDG::SpriteBatcher(50);
    batcher3D = new DBDG::SpriteBatcher3D(50);
    texture = new DBDG::GLTexture("resource/fieldAtlas.png");
    region  = new DBDG::TextureRegion(texture, 0, 0, 128, 128);
    model   = new DBDG::XfileModel("resource/gargoyle/gargoyle.x", 3);

    auto bitmap = new DBDG::GLTexture("resource/bitmapFont.png");
    font = new DBDG::GLFont(bitmap, batcher, batcher3D, /*left = */0, /*top = */0, /* glyphPerRow*/10, 51.2, 51.2);
    LightSetting();
  }
  
  void update(float deltaTime)
  {
    elapsedTime += deltaTime;
  }

  void render(float deltaTime)
  {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    camera3D->setViewportAndMatrices();
    model->renderWithColor4(DBDG::Color4(1,0,0, 0.5));

    auto dir = camera3D->getPosition() - camera3D->getLook();
    dir.z = 0;
    font->drawString3D("Hello", DBDG::Vector3(0,0,0), dir , 500, 250*sin(elapsedTime), DBDG::Color4(1,0,1,1), DBDG::Font::ALIGNMENT_CENTER);
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
  TestGame game(argc, argv, "test", 640, 320);
  game.setScene(game.getStartScene());
  
  glClearColor(1.0, 1.0, 0.0, 1.0);
  game.loop();

  return 0;
}
