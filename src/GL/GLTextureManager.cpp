#include <GL/glDBDG.h>
#include <FileIO.h>
#include <GL/GLTextureManager.h>
#include <GL/GLTexture.h>
namespace DBDG
{
  Texture* GLTextureManager::newTexture(const std::string &file_name) const
  {
    std::string full_path = FileIO::getInstance()->getRootDirectory() + file_name;
    return new GLTexture(full_path);
  }
}
