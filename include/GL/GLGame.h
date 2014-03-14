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
    static void error_callback(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
    static void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);
    static void resize_callback(GLFWwindow* window, int width, int height);
  protected:
    GLFWwindow *window;
    GLInput *input;
    GLAudio *audio;
    Scene *scene,*nextScene;
    void replaceScene();  //次のシーンがあれば入れ替える
  public:
    GLGame(int argc, char **argv, std::string window_title);
    GLGame(int argc, char **argv, std::string window_title, int window_width, int window_height, bool is_fullscreen=false);
    virtual ~GLGame();
    void loop(const float &delta_time_sec);
    bool setScene(Scene *scene);
    Input* const getInput() const;
    Audio* const getAudio()  const; 
    Scene* const getCurrentScene() const;
    GLFWwindow* getWindow() const;   //glfwの関数を扱う関係でconstにできない
  };
}
#endif
