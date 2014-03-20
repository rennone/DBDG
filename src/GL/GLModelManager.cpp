#include <GL/GLGraphic.h>
#include <GL/glDBDG.h>

namespace DBDG
{
  Model* GLModelManager::newModel(const std::string &file_name, const float &scale)
  {
    return new XfileModel(file_name, scale);
}
  
}
