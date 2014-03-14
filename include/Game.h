#ifndef DBDG_GAME_H
#define DBDG_GAME_H

namespace DBDG
{
  class Scene;
  class Input;
  class Audio;
  
  class Game
  {
  public:
    Game(){}
    virtual ~Game(){}
    virtual Input* const getInput()  const=0;
    virtual Audio* const getAudio()  const=0;
    virtual Scene* const getCurrentScene() const = 0;
    
    virtual bool setScene(Scene *scene)=0; //bool : 切り替えが成功したか否か(1ループで複数のシーンがセットされないように)
    
    virtual void loop(const float &delta_time)=0; //ゲームスタート
    virtual Scene* getStartScene() = 0;   //コンストラクタから一番始めに一回だけ呼び出される todo protectedにすべき?
  };
  
}
#endif
