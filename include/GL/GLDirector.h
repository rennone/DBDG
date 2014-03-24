#ifndef DBDG_GL_DIRECTOR_H
#define DBDG_GL_DIRECTOR_H

//ヘッダーファイルのインクルードは, ""で書いた方が良い
//外部から使うときに, そっちのmakeFileに書かれているパスに依存してしまうから
struct GLFWwindow;
namespace DBDG
{
  class GLGame;  
  class GLDirector
  {
    static GLGame *glGame;
    static float elapsedTime_sec[2];
    static float fps;
  public :
    static void startGame(GLGame *game);
    static void loop();
  private:
    GLDirector();
    GLDirector(const GLDirector &other);
    ~GLDirector();
    GLDirector& operator=(const GLDirector &other);
  };
}

#endif
