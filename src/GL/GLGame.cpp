#include <iostream> //エラー吐き出し用

//glfw glewの mac用の設定
#define GLFW_NO_GLU
#include <GL/glDBDG.h>

namespace
{
  //GLFW用のコールバック設定
  void error_callback(int error, const char* description)
  {
    fputs(description, stderr);
  }
  
  void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    DBDG::GLGame*   game = (DBDG::GLGame*)glfwGetWindowUserPointer(window);
    DBDG::GLInput* input = (DBDG::GLInput*)game->getInput();
    input->onKeyCallback(key, action, mods);
  }
  
  void mouseCallback(GLFWwindow* window, int button, int action, int mods)
  {
    DBDG::GLGame*   game = (DBDG::GLGame*)glfwGetWindowUserPointer(window);
    DBDG::GLInput* input = (DBDG::GLInput*)game->getInput();
    input->onMouseCallback(button, action, mods);
  }
  
  void scrollCallback(GLFWwindow* window, double offsetX, double offsetY)
  {
    DBDG::GLGame*   game = (DBDG::GLGame*)glfwGetWindowUserPointer(window);
    DBDG::GLInput* input = (DBDG::GLInput*)game->getInput();
    input->onScrollCallback(offsetX, offsetY);
  }

  void resize_callback(GLFWwindow* window, int width, int height)
  {
    DBDG::GLGame* game = (DBDG::GLGame*)glfwGetWindowUserPointer(window);
    auto scene = game->getCurrentScene();
    scene->reshape(width, height);
  }
}

namespace DBDG
{  
  GLGame::GLGame
  (std::string window_title, int window_width, int window_height, bool is_fullscreen)
    :scene(NULL), nextScene(NULL)
  {
    int argc = 0;
    glutInit(&argc, NULL); //コマンドライン引数はNULLにする.    
  
    glfwSetErrorCallback(error_callback);
    if(!glfwInit())
    {
      std::cerr << "cannot start glfw" << std::endl;
      exit(EXIT_FAILURE);
    }

    elapsedTime_sec[0] = glfwGetTime();
    elapsedTime_sec[1] = glfwGetTime();

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
    glfwSetWindowUserPointer(window, this); //このwindowにコールバック用にインプットを登録

    //glewはglfwMakeContextCurrentの後でなければならないらしい
    if( glewInit() != GLEW_OK )
    {
      std::cerr << "cannot start glew" << std::endl;
      exit(2);
    }

    input  = new GLInput(window);
    audio  = NULL;

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);
    glfwSetFramebufferSizeCallback(window, resize_callback);
        
  };

  GLGame::~GLGame()
  {
    delete input;
    /* 
       delete audio;
    */
    scene->dispose();  
    delete scene;
  };
  
  bool GLGame::setScene(Scene *scene)
  {
    //NULLを指定しようとしたらfalse
    if(scene == NULL)
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

  void GLGame::loop()
  {
    while(!glfwWindowShouldClose(window))
    {
      const float deltaTime_sec = elapsedTime_sec[1] - elapsedTime_sec[0];
      elapsedTime_sec[0] = glfwGetTime();

      replaceScene();
      input->update();  
      scene->update(deltaTime_sec);      
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);      
      scene->render(deltaTime_sec);        

      glFlush();  
      glfwSwapBuffers(window); //絶対必要
      glfwPollEvents();        //絶対必要
      elapsedTime_sec[1] = glfwGetTime();
    }  
    glfwDestroyWindow(window);
    glfwTerminate();  
    exit(EXIT_SUCCESS);
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

  Input* const GLGame::getInput() const
  {
    return input;
  }

  Audio* const GLGame::getAudio()  const
  {
    return audio;
  }
  
  Scene* const GLGame::getCurrentScene() const
  {
    return scene;
  }

//glfwの関数を扱う関係でconstにできない
  GLFWwindow* GLGame::getWindow() const
  {
    return window;
  }
}
