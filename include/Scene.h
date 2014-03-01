#ifndef DBDG_SCENE_H
#define DBDG_SCENE_H

namespace DBDG
{
  class Game;  //前方宣言
  class Scene
  {
  protected:
    const Game *game;
  public:
  Scene(Game *game):game(game){}
    virtual ~Scene(){}
  
    virtual void render(float deltaTime) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void reshape(int width, int height) = 0;
    virtual void dispose()=0;
  };
}
#endif
