#include <GL/util/SimpleGLFunction.h>
#include <GL/GL/glut.h>

namespace DBDG
{
  void dbdgDrawGrid(const int &gridSize,const int &xNum, const int &zNum)
  {
    glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT| GL_ENABLE_BIT);
    glPushMatrix();
    
    glDisable(GL_LIGHTING);
  
    float left  = -xNum/2.0*gridSize;
    float right = +xNum/2.0*gridSize;
    float front = -zNum/2.0*gridSize;
    float back  = +zNum/2.0*gridSize;

    float x = left;
    for(int i=0; i<=xNum; i++)
    {
      glBegin(GL_LINES);
      glVertex3d(x, 0, front);
      glVertex3d(x, 0, back);
      glEnd();
      x += gridSize;
    }

    float z = front;
    for(int i=0; i<=zNum; i++)
    {
      glBegin(GL_LINES);
      glVertex3d(left , 0, z);
      glVertex3d(right, 0, z);
      glEnd();
      z += gridSize;
    }
    glPopMatrix();
    glPopAttrib();
  }


  void dbdgDrawAxis(const int &length)
  {
    glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);
  
    glDisable(GL_LIGHTING);
    glColor3d(0,0,1);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(0,0,length);  
    glEnd();

    glColor3d(0,1,0);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(0,length,0);  
    glEnd();

    glColor3d(1,0,0);
    glBegin(GL_LINES);
    glVertex3d(0,0,0);
    glVertex3d(length,0,0);  
    glEnd();

    glPopAttrib();
  }
}
