#ifndef DBDG_GL_GAME_H
#define DBDG_GL_GAME_H

#include <string>
//ヘッダーファイルのインクルードは, ""で書いた方が良い
//外部から使うときに, そっちのmakeFileに書かれているパスに依存してしまうから
#include "../Game.h"

struct GLFWwindow;
namespace DBDG
{
  class GLInput;
  class GLScene;
  class Audio;
  class Graphic;
  
  class GLGame: public Game
  {
  public:
    GLGame(int argc, char **argv, const std::string &window_title, bool);
    GLGame(int argc, char **argv, const std::string &window_title,
           const int &window_width, const int &window_height, const bool &is_fullscreen=false);
    virtual ~GLGame();
    void loop(const float &delta_time_sec);
    bool setScene(Scene *scene);
    const Input&   getInput() const;
    const Audio&   getAudio() const;
    const Graphic& getGraphic() const;
    Scene&   getCurrentScene() const;
    GLFWwindow* getWindow() const;//glfwの関数を扱う関係でconstにできない

  private:
    GLFWwindow *window;

#ifdef DBDG_DEBUG    
    GLFWwindow *debugWindow;
#endif
    
    GLInput *input;
    Audio *audio;
    Graphic *graphic;
    Scene *scene,*nextScene;
    void replaceScene();//次のシーンがあれば入れ替える

    GLGame(const GLGame &);
    GLGame& operator=(const GLGame&);
  };
}
#endif
