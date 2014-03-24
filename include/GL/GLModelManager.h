#ifndef DBDG_GL_MODEL_MANAGER_H
#define DBDG_GL_MODEL_MANAGER_H

#include "../Graphic.h"

namespace DBDG
{
  class GLModelManager : public ModelManager
  {
  public:
    static GLModelManager* getInstance()
    {
      static GLModelManager instance;
      return &instance;
    }
    Model* newModel(const std::string &file_name, const float &scale) const;
  private:
    GLModelManager(){}
    GLModelManager( const GLModelManager &other);
    GLModelManager& operator=( const GLModelManager &other);
  };
}
#endif
