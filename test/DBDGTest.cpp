#include <GL/glDBDG.h>
#include <math/Vector3.hpp>
#include <math/Vector2.hpp>

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

public:
  TestScene(DBDG::GLGame *game)
    :DBDG::GLScene(game)
  {
    camera  = new DBDG::Camera2D(game->getWindow(), 640, 320);
    camera3D= new DBDG::Camera3D(game->getWindow(),DBDG::Vector3(500,500,500), DBDG::Vector3(0,0,0), 1, 1000, 120);
    batcher = new DBDG::SpriteBatcher(10);
    batcher3D = new DBDG::SpriteBatcher3D(10);
    texture = new DBDG::GLTexture("fieldAtlas.png");
    region  = new DBDG::TextureRegion(texture, 0, 0, 128, 128);
    model   = new DBDG::XfileModel("gargoyle.x", 3);
    LightSetting();    
  }
  
  void update(float deltaTime){ }

  void render(float deltaTime)
  {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    camera3D->setViewportAndMatrices();
    model->renderWithColor4(DBDG::Color4(1,0,0, 0.5));
    /*
    batcher3D->clearSprites();
    batcher3D->pushSprite( DBDG::Vector3(0,0,0), camera3D->getPosition()-camera3D->getLook() , DBDG::Vector2(500,500), region);
    batcher3D->drawAllSprites(texture);
    */
    glPopMatrix();
  }

  void reshape(int width, int height){ }

  void dispose(){ }  
};

class TestGame : public DBDG::GLGame
{
public :
  TestGame(const std::string title, const int window_widht, const int window_height)
    :GLGame(title, window_widht, window_height, false)
  {
    DBDG::Resource::setPathToResource("resource/");
    scene = getStartScene();
  }
  
  DBDG::Scene* getStartScene()
  {
    return new TestScene(this);
  }
};

int main()
{
  TestGame game("test", 640, 320);
  glClearColor(1.0, 1.0, 0.0, 1.0);
  game.loop();

  return 0;
}
