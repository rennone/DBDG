#ifndef DBDG_SCENE_H
#define DBDG_SCENE_H

namespace DBDG
{
  class Game;  //前方宣言
  class Scene
  {
    Scene(const Scene&); //コピーは禁止(参照, ポインタ以外で受け取ろうとするのを防ぐため)
    Scene& operator=(const Scene &);
  protected:
    const Game *game;
  public:
  Scene(Game *game):game(game){}
    virtual ~Scene(){}
  
    virtual void render(const float &deltaTime) = 0;
    virtual void update(const float &deltaTime) = 0;
    virtual void reshape(int width, int height) = 0;
    virtual void dispose()=0;
  };
}
#endif
