#ifndef DBDG_GL_GAME_H
#define DBDG_GL_GAME_H

#include <string>
//ヘッダーファイルのインクルードは, ""で書いた方が良い
//外部から使うときに, そっちのmakeFileに書かれているパスに依存してしまうから
#include "../Game.h"

struct GLFWwindow;
namespace DBDG
{
  class GLAudio;
  class GLInput;
  class GLScene;

  class GLGame: public Game
  {
  protected:
    GLFWwindow *window;
    GLInput *input;
    GLAudio *audio;
    Scene *scene,*nextScene;
    float elapsedTime_sec[2];
    void replaceScene();  //次のシーンがあれば入れ替える

  public:
    GLGame(std::string window_title, int window_width, int window_height, bool is_fullscreen=false);
    GLGame(std::string window_title);
    virtual ~GLGame();
    void loop();
    bool setScene(Scene *scene);
    Input* const getInput() const;
    Audio* const getAudio()  const; 
    Scene* const getCurrentScene() const;
    GLFWwindow* getWindow() const;   //glfwの関数を扱う関係でconstにできない
  };
}
#endif
