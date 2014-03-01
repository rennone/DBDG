#include <GL/glDBDG.h>
#include <GL/GLFW/glfw3.h>
class TestScene : public DBDG::GLScene
{
public:
  TestScene(DBDG::GLGame *game)
    :DBDG::GLScene(game)
  {
  }
  void update(float deltaTime)
  {
    
  }

  void render(float deltaTime)
  {
    
  }

  void reshape(int width, int height)
  {
    
  }

  void dispose()
  {
    
  }
  
};

class TestGame : public DBDG::GLGame
{
public :
  TestGame(const std::string title, const int window_widht, const int window_height)
    :GLGame(title, window_widht, window_height, false)
  {
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
  glClearColor(1.0, 1.0, 1.0, 1.0);
  game.loop();

  return 0;
}
