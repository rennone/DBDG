#ifdef DBDG_MAC_OS
#define GLFW_NO_GLU
#endif

#include <GL/glDBDG.h>
#include <GL/GLDirector.h>

namespace DBDG
{
  GLGame* GLDirector::glGame;
  float GLDirector::elapsedTime_sec[2];
  float GLDirector::fps;
  
  void GLDirector::startGame(GLGame *glGame)
  {
    elapsedTime_sec[0] = glfwGetTime();
    GLDirector::glGame = glGame;
    GLDirector::glGame->setScene(glGame->getStartScene());
    elapsedTime_sec[1] = glfwGetTime();
    loop();
  }
  
  void GLDirector::loop()
  {
    auto window = glGame->getWindow();
    while(!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      const float deltaTime_sec = elapsedTime_sec[1] - elapsedTime_sec[0];
      
      if(deltaTime_sec>0)
        fps = 1.0f/deltaTime_sec;
      
      elapsedTime_sec[0] = glfwGetTime();
      
      glGame->loop(deltaTime_sec);
      
      glFlush();  
      glfwSwapBuffers(window); //絶対必要
      glfwPollEvents();        //絶対必要
      elapsedTime_sec[1] = glfwGetTime();
    }  
    glfwDestroyWindow(window);
    glfwTerminate();  
    exit(EXIT_SUCCESS);
  }
  
}
