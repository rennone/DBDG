#include <GL/glDBDG.h>
#include <GL/GLGraphic.h>
#include <GL/AssimpModel.h>
#include <FileIO.h>

namespace DBDG
{
  Model* GLModelManager::newModel(const std::string &file_name, const float &scale) const
  {
    std::string full_path = FileIO::getInstance()->getRootDirectory() + file_name;
    return new AssimpModel( full_path, scale);
  }
}
