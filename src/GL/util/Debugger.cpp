#include <GL/util/Debugger.h>
/*
namespace DBDG
{
  namespace Util
  {
    Debugger::drawInfo()
    {
#ifdef DBDG_DEBUG
      glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);
      glPushMatrix();
      glDisable(GL_LIGHTING);
      glDisable(GL_DEPTH_TEST);
  
      int width, height;
      float ratio;
      glfwGetFramebufferSize(window, &width, &height);
      ratio = width / (float) height;
      glViewport(0, 0, width, height);
  
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glOrtho(0, width, 0, height, -10, 10);  
      glMatrixMode(GL_MODELVIEW); 
      glLoadIdentity();
      glColor3f(1, 1, 1);
      float x=0, y=10.3, dy=10;

      for( auto it = debugInfo.begin(); it != debugInfo.end(); it++)
      {			  
        //情報を書いた場所を記述
        renderString((*it).first, x, y);
        y+=dy;            
        //デバッグ情報の記述
        auto localDebugInfo = (*it).second;			
        for( auto it2 = localDebugInfo.begin(); it2 != localDebugInfo.end(); it2++, y+=dy)              
          renderString((*it2).first + " : " + (*it2).second, x, y);			  
      }
      glPopMatrix();
      glPopAttrib();
      clearDebugInfo();
#endif
    }
    
  }
}
*/
