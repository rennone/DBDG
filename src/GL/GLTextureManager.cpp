#include <GL/GLTextureManager.h>
#include <GL/glDBDG.h>

namespace DBDG
{
  Texture* GLTextureManager::newTexture(const std::string file_name)
  {
    return new GLTexture(file_name);
  }
}
