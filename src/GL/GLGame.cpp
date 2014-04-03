#include <iostream> //エラー吐き出し用

//glfw glewの mac用の設定
#include <GL/glDBDG.h>
#include <AL/AL/alut.h>
#include <GL/GLGame.h>
#include <AL/ALAudio.h>

#define g_GLInput GLInput::getInstance()
/*
    static void error_callback(int error, const char* description);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
    static void cursorPosCallback(GLFWwindow* window, double _x, double _y);
    static void cursorEnterCallback(GLFWwindow* window, int entered);
    static void scrollCallback(GLFWwindow* window, double offsetX, double offsetY);
    static void resize_callback(GLFWwindow* window, int width, int height);
*/
namespace DBDG
{
  //GLFW用のコールバック設定
  void error_callback(int error, const char* description)
  {
    fputs(description, stderr);
  }
  
  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    DBDG::GLGame*   game = (DBDG::GLGame*)glfwGetWindowUserPointer(window);
    DBDG::GLInput& input = (DBDG::GLInput&)game->getInput();
    input.onKeyCallback(key, action, mods);
  }
  
  void mouseCallback(GLFWwindow* window, int button, int action, int mods)
  {
    DBDG::GLGame*   game = (DBDG::GLGame*)glfwGetWindowUserPointer(window);
    DBDG::GLInput& input = (DBDG::GLInput&)game->getInput();
    input.onMouseButtonCallback(button, action, mods);
  }

  void cursorPosCallback(GLFWwindow* _window, double _x, double _y)
  {
    DBDG::GLGame*   game = (DBDG::GLGame*)glfwGetWindowUserPointer(_window);
    DBDG::GLInput& input = (DBDG::GLInput&)game->getInput();
    input.onMouseCursorCallback(_x, _y);
  }

  //カーソルがウィンドウに入った(GL_TRUE)or出て行った(GL_FALSE)時に呼ばれる
  void cursorEnterCallback(GLFWwindow* _window, int entered)
  {
    
  }
  
  void scrollCallback(GLFWwindow* window, double offsetX, double offsetY)
  {
    DBDG::GLGame*   game = (DBDG::GLGame*)glfwGetWindowUserPointer(window);
    DBDG::GLInput& input = (DBDG::GLInput&)game->getInput();
    input.onScrollCallback(offsetX, offsetY);
  }

  void resize_callback(GLFWwindow* window, int width, int height)
  {
    DBDG::GLGame* game = (DBDG::GLGame*)glfwGetWindowUserPointer(window);
    Scene &scene = game->getCurrentScene();
    scene.reshape(width, height);
  }
}

namespace DBDG
{
  GLGame::GLGame
  (int argc, char **argv, std::string window_title, int window_width, int window_height, bool is_fullscreen)
    :scene(NULL), nextScene(NULL)
  {    
    if(argc > 0)
    {
      FileIO::getInstance().setRootDirectory(FileIO::getSuperiorFolderPath(argv[0]));
    }
    
    glutInit(&argc, argv);
    alutInit(&argc, argv);
  
    glfwSetErrorCallback(error_callback);
    if(!glfwInit())
    {
      std::cerr << "cannot start glfw" << std::endl;
      exit(EXIT_FAILURE);
    }

    //windowを生成
    auto _monitor = is_fullscreen ? glfwGetPrimaryMonitor() : NULL;
    window = glfwCreateWindow(window_width, window_height, window_title.c_str(), _monitor, NULL);  
    if(!window)
    {
      std::cerr << "cannot open glfw window" << std::endl;
      glfwTerminate();
      exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this); //このwindowにコールバック用に自身を登録

    //glewInitはglfwMakeContextCurrentの後でなければならないらしい
    if( glewInit() != GLEW_OK )
    {
      std::cerr << "cannot start glew" << std::endl;
      exit(2);
    }

    input   = new GLInput();
    audio   = &ALAudio::getInstance();
    graphic = new GLGraphic();//GLGraphic::getInstance();

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetCursorPosCallback(window,cursorPosCallback);
    glfwSetCursorEnterCallback(window,cursorEnterCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetFramebufferSizeCallback(window, resize_callback);        
  };

  GLGame::~GLGame()
  {
    scene->dispose();

    if(scene != nullptr)
      delete scene;
    
    if(nextScene != nullptr)
      delete nextScene;
  };
  
  bool GLGame::setScene(Scene *scene)
  {
    //NULLを指定しようとしたらfalse
    if(scene == nullptr)
    {
      return false;
    }

    //既に別の所から次のシーンを指定されていたら, 除外する
    if(this->nextScene != NULL)
    {
      delete scene; //削除しておく
      return false;
    }

    this->nextScene = scene;  //次のシーンの決定
    return true;
  }

  void GLGame::loop(const float &delta_time_sec)
  {
    replaceScene();
    input->update();  
    scene->update(delta_time_sec);
    scene->render(delta_time_sec);
  };
  
  void GLGame::replaceScene()
  {
    if(nextScene != NULL)
    {
      delete scene;
      scene = nextScene;
      nextScene = NULL;
    }
  }

  Input& GLGame::getInput() const
  {
    return *input;
  }

  Audio& GLGame::getAudio()  const
  {
    return *audio;
  }

  Graphic& GLGame::getGraphic() const
  {
    return *graphic;
  }
  
  Scene& GLGame::getCurrentScene() const
  {
    return *scene;
  }

//glfwの関数を扱う関係でconstにできない
  GLFWwindow* GLGame::getWindow() const
  {
    return window;
  }
}
